#include <module/config/_private/_config.h>

bool ddns_Config_write(
	const ddns__Config *config,
	const char *desired_section,
	napc__Writer *writer
) {
	return PV_AGF_ddns_Config_write(config, desired_section, writer);
}
