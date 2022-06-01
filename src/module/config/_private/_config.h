#if !defined(PV_DDNS_CONFIG_h)
	#define PV_DDNS_CONFIG_h

	#include <module/config/config.h>

	/**
	 * Will be automatically created by create-config-handle-key-value.php
	 */
	bool PV_AGF_ddns_Config_handleKeyValue(
		ddns__Config *config,
		const char *key,
		const char *value
	);

	/**
	 * Will be automatically created by create-config-dump.php
	 */
	void PV_AGF_ddns_Config_dump(
		const ddns__Config *config
	);

	/**
	 * Will be automatically created by create-config-to-string.php
	 */
	bool PV_AGF_ddns_Config_write(
		const ddns__Config *config,
		const char *desired_section,
		napc__Writer *writer
	);

	#define PV_DDNS_CONFIG_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_TRACE(...)    NAPC_LOG_TRACE("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_DEBUG(...)    NAPC_LOG_DEBUG("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_INFO(...)     NAPC_LOG_INFO("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_WARNING(...)  NAPC_LOG_WARNING("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_ERROR(...)    NAPC_LOG_ERROR("ddns_config", ##__VA_ARGS__)
#endif
