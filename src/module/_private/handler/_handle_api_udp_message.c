#include <module/_private/_ddns.h>

struct api_request_context {
	const napc__IPv4Participant *client;
	napc_u8 request_identifier[16];
	const char *request_body;
};

static void _handleAPIRequest(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
);

/*
 * This function gets called whenever a message appears
 * on the UDP socket that is listening on the api.listen_port port.
 */
void PV_ddns_handleAPIUDPMessage(
	ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
) {
	napc_u8 request_hmac[32];
	napc_u8 request_iv[16]; 

	// hmac + iv + payload = 1024 bytes
	// only use 1024 bytes (MTU limit)
	if (buffer.size != 1024) {
		PV_DDNS_ERROR("Unexpected packet size %" NAPC_SIZE_PRINTF, buffer.size);

		return;
	}

	PV_DDNS_DEBUG(
		"Received API request from client (size=%" NAPC_SIZE_PRINTF ")",
		buffer.size
	);

	// cast to unsigned char to perform pointer arithmetic
	unsigned char *request = buffer.data;

	// read request hmac
	for (napc_size i = 0; i < 32; ++i) {
		request_hmac[i] = request[i];
	}

	// read request iv
	for (napc_size i = 0; i < 16; ++i) {
		request_iv[i] = request[32 + i];
	}

	unsigned char *ciphertext = request + 32 + 16;
	const char *hmac_key = instance->config.general.hashed_secret;

	// check hmac signature
	if (!napc_hmac_verify(hmac_key, request_hmac, ciphertext, 1024 - 32 - 16)) {
		PV_DDNS_SECURITY("Invalid HMAC signature.");

		napc_UDP_send(
			instance->api_udp_in,
			*client,
			"ddns_invalid_hmac",
			napc_strlen("ddns_invalid_hmac")
		);

		return;
	}

	// decrypt payload
	if (!napc_aes_decrypt(request_iv, hmac_key, ciphertext, 1024 - 32 - 16)) {
		PV_DDNS_ERROR("Failed to decrypt request.");

		return;
	}

	// check for ddns_
	if (!napc_memeql(ciphertext, "ddns_", 5)) {
		PV_DDNS_ERROR("ddns_ prefix is missing from payload.");

		return;
	}

	struct api_request_context ctx;

	// read request identifier
	for (napc_size i = 0; i < 16; ++i) {
		ctx.request_identifier[i] = ciphertext[5 + i];
	}

	char *payload = (char *)(ciphertext + 5 + 16);

	// make sure payload is always NUL-terminated
	payload[1023] = 0;

	ctx.request_body = payload;
	ctx.client = client;

	PV_ddns_useSharedBuffer(
		instance,
		"1k-buffer-2",
		&ctx,
		_handleAPIRequest
	);
}

static void _handleAPIRequest(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
) {
	struct api_request_context *ctx = context;

	NAPC_ASSERT(instance->api.random_iv_ready);

	// write operations should never fail
	napc__NFWriter writer = napc_NFWriter_create(buffer->data, 1024);

	napc_mzero(buffer->data, 1024);

	// skip hmac
	napc_NFWriter_moveCurrentOffsetByAmount(&writer, 32);

	// write IV
	const napc_u8 *response_iv = instance->api.random_iv;
	napc_NFWriter_writeU8Array(&writer, 16, response_iv);

	// write request id
	napc_NFWriter_writeU8Array(&writer, 16, ctx->request_identifier);

	// write ddns_
	napc_NFWriter_writeString(&writer, "ddns_");

	// write API_VERSION
	napc_NFWriter_writeU32BE(&writer, NAPC_U32_LITERAL(
		0x00000001
	));

	napc__Writer response_writer = napc_Writer_create(
		napc_NFWriter_getCurrentAddress(&writer),
		1024 - napc_NFWriter_getCurrentOffset(&writer)
	);

	bool result = PV_AGF_ddns_handleAPICall(
		instance,
		ctx->request_body,
		&response_writer
	);

	PV_DDNS_DEBUG("handleAPICall returned %s", result ? "success" : "failure");

	unsigned char *response = ((unsigned char *)buffer->data) + 32 + 16;
	const char *hmac_key = instance->config.general.hashed_secret;

	NAPC_IGNORE_VALUE(
		napc_aes_encrypt(response_iv, hmac_key, response, 1024 - 32 - 16)
	);

	// hmac is at the beginning of buffer
	napc_hmac_calculate(buffer->data, hmac_key, response, 1024 - 32 - 16);

	napc_UDP_send(
		instance->api_udp_in,
		*ctx->client,
		buffer->data,
		1024
	);

	// todo: remove and test
	instance->api.random_iv_ready = false;
}
