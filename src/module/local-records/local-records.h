#if !defined(DDNS_LOCALRECORDS_h)
	#define DDNS_LOCALRECORDS_h

	#include <napc.h>

	typedef struct {
		bool valid;

		napc_u32 ttl;

		char name[64];
		napc__DNSQType type;

		napc_size rd_data_length;
		napc_u8 rd_data[16];
	} ddns__LocalDNSEntry;

	typedef struct {
		ddns__LocalDNSEntry entries[16];
	} ddns__LocalRecords;

	void ddns_LocalRecords_fromString(
		ddns__LocalRecords *records,
		const char *string
	);

	void ddns_LocalRecords_dump(
		const ddns__LocalRecords *records
	);

	napc_ssize ddns_LocalRecords_getEntryByNameAndType(
		ddns__LocalRecords *records,
		const char *name,
		napc__DNSQType type
	);
#endif
