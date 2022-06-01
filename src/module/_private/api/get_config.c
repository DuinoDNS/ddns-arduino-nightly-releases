#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_get_config(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	for (napc_size i = 0; true ; ++i) {
		const char *config_section = ddns_Config_getSections()[i];

		if (!config_section) break;

		bool result = ddns_Config_write(
			&instance->config, config_section, response
		);

		if (!result) return false;
	}


	return true;
}
