#include <module/_private/_ddns.h>

void PV_ddns_useSharedBuffer(
	ddns__Instance *instance, const char *label, void *context, void (*cb)(
		ddns__Instance *instance,
		void *context,
		napc__Buffer *buffer
	)
) {
	napc_size buffer_size = 0;
	void *buffer_ptr = NULL;
	bool *buffer_busy_var = NULL;

	if (napc_streqli(label, "1k-buffer-1")) {
		buffer_ptr = instance->buffer_1k_1;
		buffer_size = sizeof(instance->buffer_1k_1);
		buffer_busy_var = &instance->buffer_1k_1_busy;
	} else if (napc_streqli(label, "1k-buffer-2")) {
		buffer_ptr = instance->buffer_1k_2;
		buffer_size = sizeof(instance->buffer_1k_2);
		buffer_busy_var = &instance->buffer_1k_2_busy;
	}

	if (!buffer_size || !buffer_ptr || !buffer_busy_var) {
		NAPC_PANIC("Invalid shared buffer label '%s'", label);
	}

	if (*buffer_busy_var) {
		NAPC_PANIC("Attempted to use buffer '%s' that is currently in use.", label);
	}

	*buffer_busy_var = true;

	napc__Buffer buf = napc_Buffer_create(buffer_ptr, buffer_size);

	cb(instance, context, &buf);

	*buffer_busy_var = false;
}
