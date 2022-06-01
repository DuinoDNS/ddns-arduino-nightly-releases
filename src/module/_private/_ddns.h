#if !defined(PV_DDNS_CORE_h)
	#define PV_DDNS_CORE_h

	#include <module/ddns.h>

	#define PV_DDNS_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns", ##__VA_ARGS__)
	#define PV_DDNS_TRACE(...)    NAPC_LOG_TRACE("ddns", ##__VA_ARGS__)
	#define PV_DDNS_DEBUG(...)    NAPC_LOG_DEBUG("ddns", ##__VA_ARGS__)
	#define PV_DDNS_INFO(...)     NAPC_LOG_INFO("ddns", ##__VA_ARGS__)
	#define PV_DDNS_WARNING(...)  NAPC_LOG_WARNING("ddns", ##__VA_ARGS__)
	#define PV_DDNS_ERROR(...)    NAPC_LOG_ERROR("ddns", ##__VA_ARGS__)
	#define PV_DDNS_SECURITY(...) NAPC_LOG_SECURITY("ddns", ##__VA_ARGS__)

	void PV_ddns_onBoot(ddns__Instance *instance);
	void PV_ddns_onLinkUp(ddns__Instance *instance);
	void PV_ddns_onLinkDown(ddns__Instance *instance);
	void PV_ddns_runLoop(ddns__Instance *instance);

	void PV_ddns_syncConfigToDisk(ddns__Instance *instance);
	void PV_ddns_syncLocalRecordsToDisk(ddns__Instance *instance);

	void PV_ddns_invalidateOldQueries(ddns__Instance *instance);
	void PV_ddns_printDebugInformation(ddns__Instance *instance);
	void PV_ddns_gatherStatisticalValues(ddns__Instance *instance);
	void PV_ddns_advertiseOnNetwork(ddns__Instance *instance);

	void PV_ddns_useSharedBuffer(
		ddns__Instance *instance, const char *label, void *context, void (*cb)(
			ddns__Instance *instance,
			void *context,
			napc__Buffer *buffer
		)
	);

	/**
	 * DNS
	 */
	void PV_ddns_handleDNSUDPMessage(
		ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
	);

	ddns__Query *PV_ddns_getQueryByRequestIdentifier(
		ddns__Instance *instance, napc_u16 dns_request_identifier
	);

	void PV_ddns_sendDNSQueryAnswer(
		ddns__Instance *instance,
		const napc__IPv4Participant *client,
		const ddns__Query *query,
		const ddns__LocalDNSEntry *entry
	);

	/**
	 * Networking / Uptream
	 */
	void PV_ddns_handleNetworkingUDPMessage(
		ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
	);

	/**
	 * API
	 */
	void PV_ddns_handleAPIUDPMessage(
		ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
	);

	bool PV_AGF_ddns_handleAPICall(
		ddns__Instance *instance,
		const char *request,
		napc__Writer *response
	);
#endif
