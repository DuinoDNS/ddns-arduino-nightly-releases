#include <module/_private/_ddns.h>

static void _handleUDPSocket(
	ddns__Instance *instance, void *context, napc__Buffer *buffer
) {
	const char *what = context;

	napc__UDPSocket udp_socket;
	void (*handler)(ddns__Instance *, napc__IPv4Participant *, napc__Buffer) = NULL;

	if (napc_streqli(what, "dns")) {
		udp_socket = instance->dns_udp_in;
		handler = PV_ddns_handleDNSUDPMessage;
	} else if (napc_streqli(what, "networking")) {
		udp_socket = instance->networking_udp_out;
		handler = PV_ddns_handleNetworkingUDPMessage;
	} else if (napc_streqli(what, "api")) {
		udp_socket = instance->api_udp_in;
		handler = PV_ddns_handleAPIUDPMessage;
	}

	if (!handler) return;

	napc__IPv4Participant client;

	if (!napc_UDP_receive(udp_socket, &client, buffer)) {
		return;
	}

	PV_DDNS_DEBUG(
		"Received %" NAPC_SIZE_PRINTF " bytes from client %s"
		" (udp_socket=%s)",
		buffer->size, client.addr, what
	);

	handler(instance, &client, *buffer);
}

void PV_ddns_runLoop(ddns__Instance *instance) {
	PV_ddns_useSharedBuffer(instance, "1k-buffer-1", (void *)"dns", _handleUDPSocket);
	PV_ddns_useSharedBuffer(instance, "1k-buffer-1", (void *)"networking", _handleUDPSocket);

	if (!instance->api.random_iv_ready) {
		bool result = napc_random_getRandomBytes(
			sizeof(instance->api.random_iv),
			instance->api.random_iv
		);

		instance->api.random_iv_ready = result;
	}

	if (instance->api.random_iv_ready) {
		PV_ddns_useSharedBuffer(instance, "1k-buffer-1", (void *)"api", _handleUDPSocket);
	}

	PV_ddns_invalidateOldQueries(instance);
	PV_ddns_printDebugInformation(instance);
	PV_ddns_gatherStatisticalValues(instance);

	if (instance->config.discovery.enabled) {
		PV_ddns_advertiseOnNetwork(instance);
	}

	napc_random_collectBytes();
}
