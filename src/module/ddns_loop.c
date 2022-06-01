#include <module/_private/_ddns.h>


void ddns_loop(ddns__Instance *instance) {
	bool eth_link_status = napc_eth_getLinkStatus();

	/*
	 * Handle internal requests
	 */
	// request.network_reset=true is like unplugging the ethernet cable
	if (instance->request.network_reset) {
		PV_DDNS_INFO("Requested network reset.");

		eth_link_status = false;

		ddns_Config_dump(&instance->config);
		ddns_LocalRecords_dump(&instance->local_records);
	}

	if (instance->request.sync_config_to_disk) {
		PV_DDNS_INFO("Requested sync to disk (config)");

		PV_ddns_syncConfigToDisk(instance);
	}

	if (instance->request.sync_records_to_disk) {
		PV_DDNS_INFO("Requested sync to disk (local records)");

		PV_ddns_syncLocalRecordsToDisk(instance);
	}

	instance->request.network_reset = false;
	instance->request.sync_config_to_disk = false;
	instance->request.sync_records_to_disk = false;

	/*
	 * Main logic
	 */
	if (eth_link_status && !instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from DOWN to UP.");

		PV_ddns_onLinkUp(instance);
	} else if (!eth_link_status && instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from UP to DOWN.");

		PV_ddns_onLinkDown(instance);
	}

	if (eth_link_status) {
		PV_ddns_runLoop(instance);
	}

	instance->eth_link_status = eth_link_status;
}
