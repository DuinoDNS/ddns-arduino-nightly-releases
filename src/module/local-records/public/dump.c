#include <module/local-records/_private/_local-records.h>

void ddns_LocalRecords_dump(
	const ddns__LocalRecords *records
) {
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(records->entries); ++i) {
		const ddns__LocalDNSEntry *entry = &records->entries[i];

		if (!entry->valid) continue;

		if (entry->rd_data_length == 4) {
			PV_DDNS_LC_INFO(
				"name = %-30s IPv4: %3d.%3d.%3d.%3d   TTL: %" NAPC_U32_PRINTF,
				entry->name,
				entry->rd_data[0],
				entry->rd_data[1],
				entry->rd_data[2],
				entry->rd_data[3],
				entry->ttl
			);
		}
	}
}
