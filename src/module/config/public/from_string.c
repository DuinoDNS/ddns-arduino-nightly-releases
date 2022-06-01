#include <module/config/_private/_config.h>

static char _line_buffer[128]; // @static
static char _key_buffer[64]; // @static
static char _value_buffer[64]; // @static

void ddns_Config_fromString(
	ddns__Config *config,
	const char *string
) {
	napc__Reader reader;

	napc_Reader_init(&reader, string, napc_strlen(string));

	while (true) {
		if (!napc_Reader_readLine(&reader, _line_buffer, sizeof(_line_buffer))) {
			break;
		}

		bool skip = !napc_parser_parseKeyValue(
			_line_buffer,
			_key_buffer, sizeof(_key_buffer),
			_value_buffer, sizeof(_value_buffer)
		);

		if (skip) continue;

		// treat general.secret separately
		if (napc_streqli(_key_buffer, "general.secret")) {
			napc_strncpy(
				config->general.secret,
				_value_buffer,
				sizeof(config->general.secret)
			);
		} else {
			PV_AGF_ddns_Config_handleKeyValue(config, _key_buffer, _value_buffer);
		}
	}

	NAPC_IGNORE_VALUE(
		napc_sha_calculate(
			config->general.secret,
			napc_strlen(config->general.secret),
			config->general.hashed_secret,
			sizeof(config->general.hashed_secret)
		)
	);
}
