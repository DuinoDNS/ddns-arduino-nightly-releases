#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_get_tracked_metric(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	napc_u16 tracked_metric = instance->config.statistics.tracked_metric;

	if (!napc_Writer_writeU16BE(response, tracked_metric)) return false;

	napc_size n_entries = NAPC_ARRAY_ELEMENTS(instance->stats.tracked_metric_data);

	if (!napc_Writer_writeU16BE(response, n_entries)) return false;

	for (napc_size i = 0; i < n_entries; ++i) {
		napc_u16 value = instance->stats.tracked_metric_data[i];

		if (!napc_Writer_writeU16BE(response, value)) return false;
	}

	return true;
}
