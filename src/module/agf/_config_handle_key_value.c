/*
 * NOTICE: This file was automatically generated.
 */
#include <module/config/_private/_config.h>

bool PV_AGF_ddns_Config_handleKeyValue(
    ddns__Config *config,
    const char *key,
    const char *value
) {
    if (napc_streqli(key, "general.config_lock")) {
        bool tmp;
        if (napc_parser_parseBoolean(value, &tmp)) {
            config->general.config_lock = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'general.config_lock' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "general.tracked_metric")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->general.tracked_metric = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'general.tracked_metric' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "debug.ip")) {
        if (napc_parser_parseIPv4Address(value, NULL)) {
            memcpy(config->debug.ip, value, sizeof(config->debug.ip));
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'debug.ip' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "debug.port")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->debug.port = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'debug.port' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "debug.level")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->debug.level = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'debug.level' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "network.mac_address")) {
        if (napc_parser_parseMACAddress(value, NULL)) {
            memcpy(config->network.mac_address, value, sizeof(config->network.mac_address));
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'network.mac_address' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "network.address")) {
        if (napc_parser_parseIPv4Address(value, NULL)) {
            memcpy(config->network.address, value, sizeof(config->network.address));
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'network.address' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "network.netmask")) {
        if (napc_parser_parseIPv4Address(value, NULL)) {
            memcpy(config->network.netmask, value, sizeof(config->network.netmask));
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'network.netmask' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "network.gateway")) {
        if (napc_parser_parseIPv4Address(value, NULL)) {
            memcpy(config->network.gateway, value, sizeof(config->network.gateway));
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'network.gateway' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "network.out_port")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->network.out_port = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'network.out_port' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "upstream.enabled")) {
        bool tmp;
        if (napc_parser_parseBoolean(value, &tmp)) {
            config->upstream.enabled = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'upstream.enabled' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "upstream.address")) {
        if (napc_parser_parseIPv4Address(value, NULL)) {
            memcpy(config->upstream.address, value, sizeof(config->upstream.address));
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'upstream.address' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "upstream.port")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->upstream.port = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'upstream.port' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "upstream.timeout")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->upstream.timeout = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'upstream.timeout' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "statistics.tracked_metric")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->statistics.tracked_metric = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'statistics.tracked_metric' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "discovery.enabled")) {
        bool tmp;
        if (napc_parser_parseBoolean(value, &tmp)) {
            config->discovery.enabled = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'discovery.enabled' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "api.enabled")) {
        bool tmp;
        if (napc_parser_parseBoolean(value, &tmp)) {
            config->api.enabled = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'api.enabled' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "api.listen_port")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->api.listen_port = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'api.listen_port' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "dns.listen_port")) {
        napc_u16 tmp;
        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {
            config->dns.listen_port = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'dns.listen_port' value is '%s'", value);
        }
    }

    if (napc_streqli(key, "dns.local_ttl")) {
        napc_u32 tmp;
        if (napc_parser_parseDecimalNumberU32(value, &tmp)) {
            config->dns.local_ttl = tmp;
            return true;
        } else {
            PV_DDNS_CONFIG_ERROR("Failed to parse value for 'dns.local_ttl' value is '%s'", value);
        }
    }

    PV_DDNS_CONFIG_ERROR("Unknown key '%s'", key);
    return false;
}
