#include <module/config/_private/_config.h>

static const char *_sections[9] = {
	"general", "debug", "network", "upstream", "api", "statistics", "discovery", "dns", NULL
}; // @static

const char * const *ddns_Config_getSections(void) {
	return _sections;
}
