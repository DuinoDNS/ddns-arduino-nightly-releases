#include <module/_private/_ddns.h>

static char _broadcast_addr[32]; // @static

void PV_ddns_advertiseOnNetwork(ddns__Instance *instance) {
	if (!napc_Timer_expired(&instance->network_advertisement_timer)) {
		return;
	}

	if (napc_eth_calculateBroadcastAddress(
		instance->config.network.address,
		instance->config.network.netmask,
		_broadcast_addr, sizeof(_broadcast_addr)
	)) {
		napc_u16 port = 50523;

		PV_DDNS_DEBUG("Advertising on broadcast addr '%s:%d'", _broadcast_addr, port);

		napc__IPv4Participant destination = napc_IPv4Participant_create(
			_broadcast_addr,
			port
		);

		napc_UDP_sendSilent(
			instance->networking_udp_out,
			destination,
			"ddns_",
			5
		);
	}

	napc_Timer_restart(&instance->network_advertisement_timer);
}
