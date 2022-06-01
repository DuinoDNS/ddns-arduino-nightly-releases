#include <module/_private/_ddns.h>

static void _syncConfigToDisk(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
) {
	NAPC_IGNORE_VALUE(context);

	napc__Writer writer = napc_Writer_create(buffer->data, buffer->size);

	if (!ddns_Config_write(&instance->config, "secret", &writer)) {
		return;
	}

	for (napc_size i = 0; true ; ++i) {
		const char *config_section = ddns_Config_getSections()[i];

		if (!config_section) break;

		bool result = ddns_Config_write(
			&instance->config, config_section, &writer
		);

		if (!result) return;
	}

	if (!napc_Writer_writeChar(&writer, 0)) return;

	NAPC_IGNORE_VALUE(
		napc_fs_writeFileCString("DUINODNS/CFG.TXT", buffer->data)
	);
}

void PV_ddns_syncConfigToDisk(ddns__Instance *instance) {
	PV_ddns_useSharedBuffer(
		instance,
		"1k-buffer-1",
		NULL,
		_syncConfigToDisk
	);
}
