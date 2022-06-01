#include <module/_private/_ddns.h>

/*
 * This function gets called whenever a message appears from the
 * upstream DNS server.
 */
void PV_ddns_handleNetworkingUDPMessage(
	ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
) {
	/*
	 * Attempt to parse DNS header because we need dns_header.request_identifier
	 */
	napc__DNSHeader dns_header;

	if (!napc_DNS_parseHeader(&dns_header, buffer.data, buffer.size)) {
		PV_DDNS_ERROR("Could not parse DNS-header. Nothing more to do.");

		return;
	}

	PV_DDNS_DEBUG(
		"Parsed DNS-Query header: request identifier is 0x%04x", dns_header.request_identifier
	);

	ddns__Query *q = PV_ddns_getQueryByRequestIdentifier(
		instance,
		dns_header.request_identifier
	);

	if (!q) {
		PV_DDNS_ERROR(
			"No query in list that is associated with"
			" the request identifier 0x%04x",
			dns_header.request_identifier
		);

		return;
	} else if (q->meta.state == DDNS_QUERY_STATE_COMPLETED) {
		PV_DDNS_ERROR("Query already in COMPLETED state.");

		return;
	} else if (q->meta.state == DDNS_QUERY_STATE_TIMEOUT) {
		PV_DDNS_ERROR("Query already in TIMEOUT state.");

		return;
	}

	NAPC_ASSERT(q->meta_initialized);

	// 29.04.2022: leaving out response
	// q->has_response = napc_DNS_parseResponse(&q->response, buffer.data, buffer.size);

	if (dns_header.truncated) {
		instance->stats.truncated_responses++;
	}

	napc_time query_latency = napc_getTimeSinceBoot() - q->meta.received_at;

	q->meta.state = DDNS_QUERY_STATE_COMPLETED;
	q->meta.completed.query_latency = query_latency;
	instance->stats.completed_queries++;

	// add latency to statistics
	if (instance->stats.avg_upstream_latency == 0) {
		instance->stats.avg_upstream_latency = query_latency;
	} else {
		double tmp = instance->stats.avg_upstream_latency;

		tmp += query_latency;
		tmp /= 2;

		instance->stats.avg_upstream_latency = tmp;
	}

	napc_UDP_send(
		instance->dns_udp_in, q->meta.requester, buffer.data, buffer.size
	);
}
