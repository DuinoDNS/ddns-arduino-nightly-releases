#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_save_config(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	instance->request.sync_config_to_disk = true;

	napc_Writer_writeString(response, "OK\n\x00");

	return true;
}
