#if !defined(PV_DDNS_LOCALRECORDS_LOG_h)
	#define PV_DDNS_LOCALRECORDS_LOG_h

	#define PV_DDNS_LC_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns_lc", ##__VA_ARGS__)
	#define PV_DDNS_LC_TRACE(...)    NAPC_LOG_TRACE("ddns_lc", ##__VA_ARGS__)
	#define PV_DDNS_LC_DEBUG(...)    NAPC_LOG_DEBUG("ddns_lc", ##__VA_ARGS__)
	#define PV_DDNS_LC_INFO(...)     NAPC_LOG_INFO("ddns_lc", ##__VA_ARGS__)
	#define PV_DDNS_LC_WARNING(...)  NAPC_LOG_WARNING("ddns_lc", ##__VA_ARGS__)
	#define PV_DDNS_LC_ERROR(...)    NAPC_LOG_ERROR("ddns_lc", ##__VA_ARGS__)
#endif
