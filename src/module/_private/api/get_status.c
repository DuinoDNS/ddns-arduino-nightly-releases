#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_get_status(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	napc_Writer_writeU8(response, instance->debug_active ? 1 : 0);

	napc_Writer_writeU32BE(response, instance->stats.incoming_queries);
	napc_Writer_writeU32BE(response, instance->stats.completed_queries);
	napc_Writer_writeU32BE(response, instance->stats.truncated_responses);
	napc_Writer_writeU32BE(response, instance->stats.timeout_queries);

	napc_Writer_writeU16BE(response, instance->stats.ticks_per_second);
	napc_Writer_writeU16BE(response, instance->stats.queries_per_second);

	napc_Writer_writeU16BE(response, instance->stats.avg_upstream_latency);

	napc_u16 random_bytes_available = napc_random_getAvailableBytes();

	napc_Writer_writeU16BE(response, random_bytes_available);
	napc_Writer_writeU32BE(response, napc_getUptime());

	return true;
}
