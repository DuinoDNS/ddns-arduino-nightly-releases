#include <module/_private/_ddns.h>

void PV_ddns_printDebugInformation(ddns__Instance *instance) {
	if (!napc_Timer_expired(&instance->debug_print_timer)) {
		return;
	}

	return;

	napc_printf(
		"Queries: %" NAPC_U32_PRINTF " / %" NAPC_U32_PRINTF "\n",
		instance->stats.completed_queries, instance->stats.incoming_queries
	);
	napc_printf("Ticks: %d\n", instance->stats.ticks_per_second);

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		napc_printf("%3" NAPC_SIZE_PRINTF ". ", i + 1);

		if (!q->meta_initialized) {
			napc_printf("not initialized");
		} else {
			napc_printf("req=%04x ", q->meta.dns_request_identifier);

			napc_printf("state=");

			if (q->meta.state == DDNS_QUERY_STATE_INITIALIZED) {
				napc_printf("INITIALIZED ");
			} else if (q->meta.state == DDNS_QUERY_STATE_TIMEOUT) {
				napc_printf("TIMEOUT     ");
			} else if (q->meta.state == DDNS_QUERY_STATE_COMPLETED) {
				napc_printf("COMPLETED   ");
			} else {
				napc_printf("UNKNOWN     ");
			}

			if (q->has_request) {
				napc_printf(
					"%s (QTYPE=%d)",
					q->request.query.name,
					q->request.query.qtype
				);
			}

			if (q->meta.state == DDNS_QUERY_STATE_COMPLETED) {
				napc_printf(" (latency=%" NAPC_TIME_PRINTF "ms) ", q->meta.completed.query_latency);
			}
		}

		napc_printf("\n");
	}

	napc_Timer_restart(&instance->debug_print_timer);
}
