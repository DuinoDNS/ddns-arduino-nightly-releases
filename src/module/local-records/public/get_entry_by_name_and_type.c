#include <module/local-records/_private/_local-records.h>

napc_ssize ddns_LocalRecords_getEntryByNameAndType(
	ddns__LocalRecords *records,
	const char *name,
	napc__DNSQType type
) {
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(records->entries); ++i) {
		if (!records->entries[i].valid) continue;

		if (
			napc_streqli(records->entries[i].name, name) &&
			records->entries[i].type == type) {
			return i;
		}
	}

	return -1;
}
