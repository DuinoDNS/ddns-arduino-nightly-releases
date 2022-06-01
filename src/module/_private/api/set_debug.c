#include <module/_private/_ddns.h>

static char _msg_buffer[512]; // @static

static void _debugHandler(
	void *context,
	const char *subsys,
	int level,
	const char *function,
	const char *message
) {
	ddns__Instance *instance = context;

	if (!instance->eth_link_status) {
		return;
	}

	napc_snprintf(
		_msg_buffer, sizeof(_msg_buffer), "%s,%d,%s,%s\n",
		subsys,
		level,
		function,
		message
	);

	napc_UDP_sendSilent(
		instance->networking_udp_out,
		napc_IPv4Participant_create(
			instance->config.debug.ip,
			instance->config.debug.port
		),
		_msg_buffer,
		napc_strlen(_msg_buffer)
	);
}

bool PV_ddns_handleAPICall_set_debug(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	if (instance->debug_active) {
		return false;
	}

	instance->debug_active = true;

	instance->debug_log_handler_index = napc_addLogHandlerFunction(
		_debugHandler,
		instance
	);

	napc_Writer_writeString(response, "Successfully set debug\n\x00");

	return true;
}
