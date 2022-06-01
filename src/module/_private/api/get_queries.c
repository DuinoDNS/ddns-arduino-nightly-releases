#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_get_queries(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	napc_Writer_writeU32BE(response, instance->stats.incoming_queries);
	napc_Writer_writeU32BE(response, instance->stats.completed_queries);

	napc_Writer_writeU8(response, NAPC_ARRAY_ELEMENTS(instance->queries));

	// 9 bytes

		// per iteration:
			// 1 byte (meta_initialized)
			// 2 byte (request identifier)
			// 1 byte (meta state)
			// 4 byte (latency)
			// 1 byte (include_request_data)
			// --> 9 bytes fixed

	// full: 64 bytes + 1 + 1 --> 66 bytes

	// full: 66 bytes + 9 bytes = 75 bytes
	// slim: 9 bytes            = 9 bytes


	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		napc_Writer_writeChar(response, q->meta_initialized ? 'y' : 'n');

		if (!q->meta_initialized) continue;

		napc_Writer_writeU16BE(response, q->meta.dns_request_identifier);
		napc_Writer_writeU8(response, q->meta.state);

		if (q->meta.state == DDNS_QUERY_STATE_COMPLETED) {
			napc_Writer_writeU32BE(response, q->meta.completed.query_latency);
		}

		/*
		 * Only include request data for the most recent queries.
		 * This is because UDP packet is sized at 1024 bytes
		 * making sending all request data for every query impossible:
		 *
		 * 32 queries * 64 bytes (name) = 2048 bytes
		 */
		bool include_request_data = q->has_request;

		if (i >= 8) {
			include_request_data = false;
		}

		napc_Writer_writeChar(response, include_request_data ? 'y' : 'n');

		if (!include_request_data) continue;

		napc_Writer_writeString(response, q->request.query.name);
		napc_Writer_writeChar(response, 0);
		napc_Writer_writeU8(response, q->request.query.qtype);
	}

	return true;
}
