#include <module/_private/_ddns.h>

/*
 * This function gets called whenever a message appears
 * on the UDP socket that is listening on the dns.listen_port port.
 */
void PV_ddns_handleDNSUDPMessage(
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

	instance->stats.incoming_queries++;

	/*
	 * Check if the request is already in instance->queries list.
	 */
	ddns__Query *q = PV_ddns_getQueryByRequestIdentifier(
		instance,
		dns_header.request_identifier
	);

	if (q && q->meta_initialized) {
		PV_DDNS_WARNING(
			"Ignoring DNS-Query because it is already in the queries list."
		);

		return;
	}

	/*
	 * Check the tail of the list before discarding the
	 * last element of it.
	 */
	ddns__Query *tail = &instance->queries[
		NAPC_ARRAY_ELEMENTS(instance->queries) - 1
	];

	if (tail->meta_initialized) {
		PV_DDNS_DEBUG("Tail of query backlog is valid. Checking ... ");

		if (tail->meta.state == DDNS_QUERY_STATE_INITIALIZED) {
			PV_DDNS_WARNING(
				"Refusing to throw away pending DNS request."
			);

			return;
		}
	}

	// do the shifting
	napc_misc_shiftArrayRight(
		instance->queries,
		NAPC_ARRAY_ELEMENTS(instance->queries),
		sizeof(ddns__Query)
	);

	// set the initial query data
	ddns__Query *head = &instance->queries[0];

	head->meta.requester = *client;
	head->meta.received_at = napc_getTimeSinceBoot();
	head->meta.dns_request_identifier = dns_header.request_identifier;
	head->meta.state = DDNS_QUERY_STATE_INITIALIZED;
	head->meta_initialized = true;

	head->has_request = napc_DNS_parseRequest(&head->request, buffer.data, buffer.size);

	// 29.04.2022: leaving out response
	//head->has_response = false;

	// try to resolve query..
	if (head->has_request) {
		PV_DDNS_DEBUG(
			"Successfully parsed DNS-Request (name=%s, type=%d)",
			head->request.query.name,
			head->request.query.qtype
		);

		napc_ssize local_entry_index = ddns_LocalRecords_getEntryByNameAndType(
			&instance->local_records,
			head->request.query.name,
			head->request.query.qtype
		);

		if (local_entry_index >= 0) {
			PV_DDNS_INFO(
				"Successfully found a matching local DNS record at index %" NAPC_SSIZE_PRINTF,
				local_entry_index
			);

			PV_ddns_sendDNSQueryAnswer(
				instance,
				client,
				head,
				&instance->local_records.entries[local_entry_index]
			);

			head->meta.state = DDNS_QUERY_STATE_COMPLETED;
			head->meta.completed.query_latency = 0;
			// 29.04.2022: leaving out response
			//head->has_response = false;

			instance->stats.completed_queries++;

			return;
		}
	}

	if (!instance->config.upstream.enabled) {
		PV_DDNS_WARNING(
			"Relaying DNS requests to upstream has been disabled."
		);

		return;
	}

	PV_DDNS_INFO(
		"Cannot resolve query locally, sending to upstream %s:%d",
		instance->config.upstream.address, instance->config.upstream.port
	);

	napc_UDP_send(
		instance->networking_udp_out,
		napc_IPv4Participant_create(
			instance->config.upstream.address,
			instance->config.upstream.port
		),
		buffer.data,
		buffer.size
	);
}
