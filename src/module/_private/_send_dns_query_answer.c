#include <module/_private/_ddns.h>

static napc_u8 _response_buffer[100]; // @static
static char _tmp_label_buffer[128]; // @static

void PV_ddns_sendDNSQueryAnswer(
	ddns__Instance *instance,
	const napc__IPv4Participant *client,
	const ddns__Query *query,
	const ddns__LocalDNSEntry *entry
) {
	const char *requested_name = query->request.query.name;
	char *label_saveptr = NULL;

	napc__NFWriter response_writer = napc_NFWriter_create(
		_response_buffer,
		sizeof(_response_buffer)
	);

	napc__NFWriter *wr = &response_writer;

	/**
	 * Write DNS header
	 */
	napc_NFWriter_writeU16BE(wr, query->request.header.request_identifier);
	napc_NFWriter_writeU16BE(wr, query->request.header.raw_flags | NAPC_U16_LITERAL(0x8000));
	napc_NFWriter_writeU16BE(wr, 1); // QD
	napc_NFWriter_writeU16BE(wr, 1); // AN
	napc_NFWriter_writeU16BE(wr, 0);
	napc_NFWriter_writeU16BE(wr, 0);

	/**
	 * Encode name into DNS labels
	 */
	napc_strncpy(_tmp_label_buffer, requested_name, sizeof(_tmp_label_buffer));

	const char *label = strtok_r(_tmp_label_buffer, ".", &label_saveptr);

	while (label) {
		napc_u8 label_size = napc_strlen(label);

		napc_NFWriter_writeU8(wr, label_size);
		napc_NFWriter_writeString(wr, label);

		label = strtok_r(NULL, ".", &label_saveptr);
	}

	napc_NFWriter_writeU8(wr, 0); // end of label section
	napc_NFWriter_writeU16BE(wr, 1); // QTYPE
	napc_NFWriter_writeU16BE(wr, 1); // QCLASS

	/**
	 * 
	 */

	// 0xc00c -> points to name
	napc_NFWriter_writeU16BE(wr, 0xc00c);

	napc_NFWriter_writeU16BE(wr, 1); // QTYPE
	napc_NFWriter_writeU16BE(wr, 1); // QCLASS

	napc_NFWriter_writeU32BE(wr, entry->ttl); // ttl
	napc_NFWriter_writeU16BE(wr, entry->rd_data_length); // rd_length

	// write RD-Data
	napc_NFWriter_writeU8Array(wr, entry->rd_data_length, entry->rd_data);

	/**
	 * Send answer to client
	 */
	napc_UDP_send(
		instance->dns_udp_in, 
		*client,
		_response_buffer,
		napc_NFWriter_getCurrentOffset(wr)
	);
}
