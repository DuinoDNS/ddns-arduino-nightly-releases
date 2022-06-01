#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_clear_debug(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	if (!instance->debug_active) {
		return false;
	}

	instance->debug_active = false;

	napc_removeLogHandlerFunction(instance->debug_log_handler_index);

	napc_Writer_writeString(response, "Successfully clear debug\n\x00");

	return true;
}
