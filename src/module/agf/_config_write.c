/*
 * NOTICE: This file was automatically generated.
 */
#include <module/config/_private/_config.h>

bool PV_AGF_ddns_Config_write(
    const ddns__Config *config,
    const char *desired_section,
    napc__Writer *writer
) {
    if (napc_streqli(desired_section, "secret")) {
        if (!napc_Writer_writeString(writer, "general.secret,")) return false;
        if (!napc_Writer_writeString(writer, config->general.secret)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;
        return true;
    }

    /* general */
    if (napc_streqli(desired_section, "general")) {
        if (!napc_Writer_writeString(writer, "general.config_lock,")) return false;
        if (config->general.config_lock) {
            if (!napc_Writer_writeString(writer, "true")) return false;
        } else {
            if (!napc_Writer_writeString(writer, "false")) return false;
        }
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "general.tracked_metric,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->general.tracked_metric)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    /* debug */
    if (napc_streqli(desired_section, "debug")) {
        if (!napc_Writer_writeString(writer, "debug.ip,")) return false;
        if (!napc_Writer_writeString(writer, config->debug.ip)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "debug.port,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->debug.port)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "debug.level,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->debug.level)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    /* network */
    if (napc_streqli(desired_section, "network")) {
        if (!napc_Writer_writeString(writer, "network.mac_address,")) return false;
        if (!napc_Writer_writeString(writer, config->network.mac_address)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "network.address,")) return false;
        if (!napc_Writer_writeString(writer, config->network.address)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "network.netmask,")) return false;
        if (!napc_Writer_writeString(writer, config->network.netmask)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "network.gateway,")) return false;
        if (!napc_Writer_writeString(writer, config->network.gateway)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "network.out_port,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->network.out_port)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    /* upstream */
    if (napc_streqli(desired_section, "upstream")) {
        if (!napc_Writer_writeString(writer, "upstream.enabled,")) return false;
        if (config->upstream.enabled) {
            if (!napc_Writer_writeString(writer, "true")) return false;
        } else {
            if (!napc_Writer_writeString(writer, "false")) return false;
        }
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "upstream.address,")) return false;
        if (!napc_Writer_writeString(writer, config->upstream.address)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "upstream.port,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->upstream.port)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "upstream.timeout,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->upstream.timeout)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    /* statistics */
    if (napc_streqli(desired_section, "statistics")) {
        if (!napc_Writer_writeString(writer, "statistics.tracked_metric,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->statistics.tracked_metric)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    /* discovery */
    if (napc_streqli(desired_section, "discovery")) {
        if (!napc_Writer_writeString(writer, "discovery.enabled,")) return false;
        if (config->discovery.enabled) {
            if (!napc_Writer_writeString(writer, "true")) return false;
        } else {
            if (!napc_Writer_writeString(writer, "false")) return false;
        }
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    /* api */
    if (napc_streqli(desired_section, "api")) {
        if (!napc_Writer_writeString(writer, "api.enabled,")) return false;
        if (config->api.enabled) {
            if (!napc_Writer_writeString(writer, "true")) return false;
        } else {
            if (!napc_Writer_writeString(writer, "false")) return false;
        }
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "api.listen_port,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->api.listen_port)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    /* dns */
    if (napc_streqli(desired_section, "dns")) {
        if (!napc_Writer_writeString(writer, "dns.listen_port,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U16_PRINTF, config->dns.listen_port)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        if (!napc_Writer_writeString(writer, "dns.local_ttl,")) return false;
        if (!napc_Writer_writeStringFormat(writer, "%" NAPC_U32_PRINTF, config->dns.local_ttl)) return false;
        if (!napc_Writer_writeChar(writer, '\n')) return false;

        return true;
    }
    return false;
}
