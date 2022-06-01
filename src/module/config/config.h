#if !defined(DDNS_CONFIG_h)
	#define DDNS_CONFIG_h

	#include <napc.h>

	#define DDNS_CONFIG_TRACKED_METRIC_TPS               1u
	#define DDNS_CONFIG_TRACKED_METRIC_UPSTREAM_LATENCY  2u

	typedef struct {
		struct {
			char      secret[65];
			char      hashed_secret[65];
			bool      config_lock;
			napc_u16  tracked_metric;
		} general;

		struct {
			char      ip[NAPC_MODULE_NET_IP_STR_MAX];
			napc_u16  port;
			napc_u16  level;
		} debug;

		struct {
			char      mac_address[64];
			char      address[NAPC_MODULE_NET_IP_STR_MAX];
			char      netmask[NAPC_MODULE_NET_IP_STR_MAX];
			char      gateway[NAPC_MODULE_NET_IP_STR_MAX];
			napc_u16  out_port;
		} network;

		struct {
			bool      enabled;
			char      address[NAPC_MODULE_NET_IP_STR_MAX];
			napc_u16  port;
			napc_u16  timeout;
		} upstream;

		struct {
			napc_u16 tracked_metric;
		} statistics;

		struct {
			bool      enabled;
		} discovery;

		struct {
			bool      enabled;
			napc_u16  listen_port;
		} api;

		struct {
			napc_u16  listen_port;
			napc_u32  local_ttl;
		} dns;
	} ddns__Config;

	void ddns_Config_setDefaults(
		ddns__Config *config
	);

	void ddns_Config_fromString(
		ddns__Config *config,
		const char *string
	);

	void ddns_Config_dump(
		const ddns__Config *config
	);

	bool ddns_Config_write(
		const ddns__Config *config,
		const char *desired_section,
		napc__Writer *writer
	) NAPC_FN_WARNUNUSED_RET();

	const char * const *ddns_Config_getSections(void);
#endif
