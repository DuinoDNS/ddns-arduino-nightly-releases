#include <module/_private/_ddns.h>

ddns__Query *PV_ddns_getQueryByRequestIdentifier(
	ddns__Instance *instance, napc_u16 dns_request_identifier
) {
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		if (!q->meta_initialized) continue;

		if (q->meta.dns_request_identifier == dns_request_identifier) {
			return q;
		}
	}

	return NULL;
}
