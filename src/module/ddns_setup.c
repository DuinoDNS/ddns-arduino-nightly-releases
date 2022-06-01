#include <module/_private/_ddns.h>

void ddns_setup(
	ddns__Instance *instance,
	const char *config_file_path,
	const char *records_file_path
) {
	PV_DDNS_INFO("Initializing instance.");

	/**
	 * Init core variables
	 */
	instance->eth_link_status = false;
	instance->debug_active = false;
	instance->buffer_1k_1_busy = false;
	instance->buffer_1k_2_busy = false;

	/**
	 * Set config defaults and then attempt to
	 * read configuration.
	 */
	ddns_Config_setDefaults(&instance->config);

	{
		if (napc_fs_readFileCString(config_file_path, instance->buffer_1k_1, sizeof(instance->buffer_1k_1))) {
			ddns_Config_fromString(&instance->config, instance->buffer_1k_1);
		}
	}

	{
		if (napc_fs_readFileCString(records_file_path, instance->buffer_1k_1, sizeof(instance->buffer_1k_1))) {
			ddns_LocalRecords_fromString(&instance->local_records, instance->buffer_1k_1);
		}
	}

	ddns_Config_dump(&instance->config);
	ddns_LocalRecords_dump(&instance->local_records);

	instance->config_file_path = config_file_path;
	instance->records_file_path = records_file_path;

	instance->request.network_reset = false;
	instance->request.sync_config_to_disk = false;
	instance->request.sync_records_to_disk = false;

	/**
	 * This function is only called ONCE in the program's lifecycle
	 */
	PV_ddns_onBoot(instance);
}
