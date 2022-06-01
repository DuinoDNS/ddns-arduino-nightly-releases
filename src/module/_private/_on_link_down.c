#include <module/_private/_ddns.h>

void PV_ddns_onLinkDown(ddns__Instance *instance) {
	napc_UDP_closeSocket(instance->dns_udp_in);
	napc_UDP_closeSocket(instance->networking_udp_out);
	napc_UDP_closeSocket(instance->api_udp_in);
}
