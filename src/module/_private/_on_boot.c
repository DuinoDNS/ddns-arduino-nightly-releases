#include <module/_private/_ddns.h>

void PV_ddns_onBoot(ddns__Instance *instance) {
	napc_Timer_init(&instance->debug_print_timer, 2500);
	napc_Timer_start(&instance->debug_print_timer);

	napc_Timer_init(&instance->network_advertisement_timer, 5000);

	napc_Timer_init(&instance->statistics_timer, 1000);
	napc_Timer_start(&instance->statistics_timer);

	instance->stats.incoming_queries = 0;
	instance->stats.completed_queries = 0;
	instance->stats.truncated_responses = 0;
	instance->stats.timeout_queries = 0;

	instance->stats.queries_per_second = 0;
	instance->stats.ticks_per_second = 0;

	instance->stats._current_ticks_count = 0;
	instance->stats._current_queries_count = 0;
}
