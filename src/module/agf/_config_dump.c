/*
 * NOTICE: This file was automatically generated.
 */
#include <module/config/_private/_config.h>

void PV_AGF_ddns_Config_dump(
    const ddns__Config *config
) {
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* general");
    PV_DDNS_CONFIG_INFO("    config_lock      = %s", config->general.config_lock ? "yes" : "no");
    PV_DDNS_CONFIG_INFO("    tracked_metric   = %" NAPC_U16_PRINTF, config->general.tracked_metric);
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* debug");
    PV_DDNS_CONFIG_INFO("    ip               = %s", config->debug.ip);
    PV_DDNS_CONFIG_INFO("    port             = %" NAPC_U16_PRINTF, config->debug.port);
    PV_DDNS_CONFIG_INFO("    level            = %" NAPC_U16_PRINTF, config->debug.level);
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* network");
    PV_DDNS_CONFIG_INFO("    mac_address      = %s", config->network.mac_address);
    PV_DDNS_CONFIG_INFO("    address          = %s", config->network.address);
    PV_DDNS_CONFIG_INFO("    netmask          = %s", config->network.netmask);
    PV_DDNS_CONFIG_INFO("    gateway          = %s", config->network.gateway);
    PV_DDNS_CONFIG_INFO("    out_port         = %" NAPC_U16_PRINTF, config->network.out_port);
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* upstream");
    PV_DDNS_CONFIG_INFO("    enabled          = %s", config->upstream.enabled ? "yes" : "no");
    PV_DDNS_CONFIG_INFO("    address          = %s", config->upstream.address);
    PV_DDNS_CONFIG_INFO("    port             = %" NAPC_U16_PRINTF, config->upstream.port);
    PV_DDNS_CONFIG_INFO("    timeout          = %" NAPC_U16_PRINTF, config->upstream.timeout);
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* statistics");
    PV_DDNS_CONFIG_INFO("    tracked_metric   = %" NAPC_U16_PRINTF, config->statistics.tracked_metric);
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* discovery");
    PV_DDNS_CONFIG_INFO("    enabled          = %s", config->discovery.enabled ? "yes" : "no");
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* api");
    PV_DDNS_CONFIG_INFO("    enabled          = %s", config->api.enabled ? "yes" : "no");
    PV_DDNS_CONFIG_INFO("    listen_port      = %" NAPC_U16_PRINTF, config->api.listen_port);
    PV_DDNS_CONFIG_INFO(" ");
    PV_DDNS_CONFIG_INFO("* dns");
    PV_DDNS_CONFIG_INFO("    listen_port      = %" NAPC_U16_PRINTF, config->dns.listen_port);
    PV_DDNS_CONFIG_INFO("    local_ttl        = %" NAPC_U32_PRINTF, config->dns.local_ttl);
    PV_DDNS_CONFIG_INFO(" ");
}
