#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_restart(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	instance->request.network_reset = true;

	napc_Writer_writeString(response, "OK\n\x00");

	return true;
}
