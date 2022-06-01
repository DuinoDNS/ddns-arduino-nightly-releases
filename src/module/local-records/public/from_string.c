#include <module/local-records/_private/_local-records.h>

static char _line_buffer[256]; // @static
//static char _tmp_buffer[128]; // @static

static napc_size _countCommas(const char *line) {
	napc_size commas = 0;

	for (napc_size i = 0; i < napc_strlen(line); ++i) {
		if (line[i] == ',') {
			commas++;
		}
	}

	return commas;
}

static bool _parseLine(ddns__LocalDNSEntry *target, char *line) {
	napc_size n_commas = _countCommas(line);

	if (n_commas != 1 && n_commas != 2 && n_commas != 3) {
		return false;
	}

	// NAME,IP (A record, default TTL)
	// TYPE,NAME,IP
	// TYPE,TTL,NAME,IP

	char *saveptr = NULL;
	const char *token = strtok_r(line, ",", &saveptr);
	const char *operation = "";
	napc_size i = 0;

	// type is needed for parsing rd-data
	bool type_fetched = false;

	target->ttl = 0;
	target->rd_data_length = 0;

	while (token) {
		operation = "";

		// NAME,IP
		if (n_commas == 1) {
			if (i == 0) {
				operation = "fetch-name";

				target->type = NAPC_DNS_QTYPE_A;
				type_fetched = true;
			} else if (i == 1) {
				operation = "fetch-rd-data";
			}
		}
		// TYPE,NAME,IP
		else if (n_commas == 2) {
			if (i == 0) {
				operation = "fetch-type";
			} else if (i == 1) {
				operation = "fetch-name";
			} else if (i == 2) {
				operation = "fetch-rd-data";
			}
		}
		// TYPE,TTL,NAME.IP
		else {
			if (i == 0) {
				operation = "fetch-type";
			} else if (i == 1) {
				operation = "fetch-ttl";
			} else if (i == 2) {
				operation = "fetch-name";
			} else if (i == 3) {
				operation = "fetch-rd-data";
			}
		}

		PV_DDNS_LC_DEBUG("Handling token '%s' (n_commas=%lu,op=%s)", token, n_commas, operation);

		if (napc_streql("fetch-name", operation)) {
			napc_strncpy(
				target->name, token, sizeof(target->name)
			);
		} else if (napc_streql("fetch-type", operation)) {
			if (napc_streql("A", token)) {
				target->type = NAPC_DNS_QTYPE_A;
			} else if (napc_streql("AAAA", token)) {
				target->type = NAPC_DNS_QTYPE_AAAA;
			} else {
				PV_DDNS_LC_WARNING("Invalid type '%s'", token);

				return false;
			}

			type_fetched = true;
		} else if (napc_streql("fetch-ttl", operation)) {
			if (!napc_parser_parseDecimalNumberU32(token, &target->ttl)) {
				PV_DDNS_LC_WARNING("Failed to parse TTL.");

				return false;
			}
		} else if (napc_streql("fetch-rd-data", operation)) {
			NAPC_ASSERT(type_fetched);

			switch (target->type) {
				case NAPC_DNS_QTYPE_A: {
					if (!napc_parser_parseIPv4Address(token, target->rd_data)) {
						PV_DDNS_LC_WARNING("Failed to parse IPv4Address '%s'", token);

						return false;
					}

					target->rd_data_length = 4;
				} break;

				case NAPC_DNS_QTYPE_AAAA: {
				} break;

				default: {

				} break;
			}
		} else {
			PV_DDNS_LC_ERROR("Invalid parse operation '%s'", operation);

			return false;
		}

		token = strtok_r(NULL, ",", &saveptr);
		++i;
	}

	target->valid = true;

	return true;
}

void ddns_LocalRecords_fromString(
	ddns__LocalRecords *records,
	const char *string
) {
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(records->entries); ++i) {
		records->entries[i].valid = false;
	}

	napc_size current_index = 0;
	//napc_size max_entries = NAPC_ARRAY_ELEMENTS(records->entries);

	napc__Reader reader;
	napc_Reader_init(&reader, string, napc_strlen(string));

	while (true) {
		if (!napc_Reader_readLine(&reader, _line_buffer, sizeof(_line_buffer))) {
			break;
		}

		ddns__LocalDNSEntry *target = &records->entries[current_index];

		if (!_parseLine(target, _line_buffer)) {
			PV_DDNS_LC_WARNING("Invalid DNS-Entry '%s'", _line_buffer);
		} else {
			NAPC_ASSERT(target->valid);

			PV_DDNS_LC_INFO(
				"Parsed DNS-Entry name=%s,type=%u,rd_data_length=%" NAPC_SIZE_PRINTF ",ttl=%" NAPC_U32_PRINTF,
				target->name, target->type, target->rd_data_length, target->ttl
			);

			++current_index;
		}
	}
}
