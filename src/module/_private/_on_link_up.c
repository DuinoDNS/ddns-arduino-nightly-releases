#include <module/_private/_ddns.h>

void PV_ddns_onLinkUp(ddns__Instance *instance) {
	// init ethernet
	napc_eth_setMACAddress(instance->config.network.mac_address);
	napc_eth_setIPAddress(instance->config.network.address);
	napc_eth_setSubnetMask(instance->config.network.netmask);
	napc_eth_setGatewayAddress(instance->config.network.gateway);

	instance->dns_udp_in = napc_UDP_createSocket(instance->config.dns.listen_port);
	instance->networking_udp_out = napc_UDP_createSocket(instance->config.network.out_port);
	instance->api_udp_in = napc_UDP_createSocket(instance->config.api.listen_port);

	// init queries
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		q->meta_initialized = false;
	}

	instance->api.random_iv_ready = false;

	instance->stats.avg_upstream_latency = 0;

	PV_DDNS_DEBUG("Initializing tracked metric's data array");

	// initialize tracked metrics data array
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->stats.tracked_metric_data); ++i) {
		instance->stats.tracked_metric_data[i] = NAPC_U16_LITERAL(0xFFFF);
	}
}
