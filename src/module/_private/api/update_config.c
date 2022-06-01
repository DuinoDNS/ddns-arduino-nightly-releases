#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_update_config(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	napc_printf("update config: %s\n", request);

	ddns_Config_fromString(&instance->config, request);

	ddns_Config_dump(&instance->config);

	instance->request.network_reset = true;

	return true;
}
