#include <module/_private/_ddns.h>

void PV_ddns_invalidateOldQueries(ddns__Instance *instance) {
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		if (!q->meta_initialized) continue;
		if (q->meta.state != DDNS_QUERY_STATE_INITIALIZED) continue;

		napc_time delta = napc_getTimeSinceBoot() - q->meta.received_at;

		if (delta >= instance->config.upstream.timeout) {
			q->meta.state = DDNS_QUERY_STATE_TIMEOUT;

			instance->stats.timeout_queries++;
		}
	}
}
