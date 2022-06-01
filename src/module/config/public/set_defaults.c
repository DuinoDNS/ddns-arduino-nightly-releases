#include <module/config/_private/_config.h>

static void _setIPAddress(char *dest, const char *ip) {
	napc_strncpy(dest, ip, NAPC_MODULE_NET_IP_STR_MAX);
}

void ddns_Config_setDefaults(
	ddns__Config *config
) {
	/**
	 * General
	 */
	memset(config->general.secret, 'x', sizeof(config->general.secret));
	config->general.secret[sizeof(config->general.secret) - 1] = 0;

	memset(config->general.hashed_secret, 'x', sizeof(config->general.hashed_secret));
	config->general.hashed_secret[sizeof(config->general.hashed_secret) - 1] = 0;

	config->general.config_lock = false;
	config->general.tracked_metric = 0;

	/**
	 * Debug
	 */
	_setIPAddress(config->debug.ip, "0.0.0.0");
	config->debug.port = 0;
	config->debug.level = 0;

	/**
	 * Network
	 */
	_setIPAddress(config->network.address, "192.168.1.2");
	_setIPAddress(config->network.netmask, "255.255.255.0");
	_setIPAddress(config->network.gateway, "192.168.1.1");
	napc_strncpy(
		config->network.mac_address,
		"aa:bb:cc:dd:ee:ff",
		sizeof(config->network.mac_address)
	);
	config->network.out_port = 5555;

	/**
	 * Upstream
	 */
	config->upstream.enabled = true;
	_setIPAddress(config->upstream.address, "1.1.1.1");
	config->upstream.port = 53;
	config->upstream.timeout = 125;

	/**
	 * Statistics
	 */
	config->statistics.tracked_metric = DDNS_CONFIG_TRACKED_METRIC_TPS;

	/**
	 * Discovery
	 */
	config->discovery.enabled = true;

	/**
	 * API
	 */
	config->api.enabled = true;
	config->api.listen_port = 9090;

	/**
	 * DNS
	 */
	config->dns.listen_port = 53;
	config->dns.local_ttl = 0;
}
