#include <module/_private/_ddns.h>

void PV_ddns_gatherStatisticalValues(ddns__Instance *instance) {
	++instance->stats._current_ticks_count;

	if (!napc_Timer_expired(&instance->statistics_timer)) {
		return;
	}

	instance->stats.ticks_per_second = instance->stats._current_ticks_count;
	instance->stats._current_ticks_count = 0;

	/*
	 * Tracked metric data
	 */
	napc_u16 tracked_metric_value = NAPC_U16_LITERAL(0xFFFF);

	switch (instance->config.statistics.tracked_metric) {
		case DDNS_CONFIG_TRACKED_METRIC_TPS: {
			tracked_metric_value = instance->stats.ticks_per_second;
		} break;

		case DDNS_CONFIG_TRACKED_METRIC_UPSTREAM_LATENCY: {
			tracked_metric_value = instance->stats.avg_upstream_latency;
		} break;
	}

	napc_misc_shiftArrayRight(
		instance->stats.tracked_metric_data,
		NAPC_ARRAY_ELEMENTS(instance->stats.tracked_metric_data),
		sizeof(instance->stats.tracked_metric_data[0])
	);

	instance->stats.tracked_metric_data[0] = tracked_metric_value;

	napc_Timer_restart(&instance->statistics_timer);
}
