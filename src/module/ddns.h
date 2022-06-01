#if !defined(DDNS_CORE_h)
	#define DDNS_CORE_h

	#include <napc.h>
	#include <module/config/config.h>
	#include <module/local-records/local-records.h>

	#define DDNS_QUERY_STATE_INITIALIZED 1
	#define DDNS_QUERY_STATE_COMPLETED   2
	#define DDNS_QUERY_STATE_TIMEOUT     3

	typedef struct {
		bool meta_initialized;

		struct {
			napc_u16 dns_request_identifier;
			napc_time received_at;
			napc__IPv4Participant requester;
			napc_u8 state;

			struct {
				napc_time query_latency;
			} completed;
		} meta;

		bool has_request;
		napc__DNSRequest request;
	} ddns__Query;

	typedef struct ddns__Instance {
		bool eth_link_status;

		struct {
			bool network_reset;
			bool sync_config_to_disk;
			bool sync_records_to_disk;
		} request;

		const char *config_file_path;
		const char *records_file_path;

		ddns__Config config;
		ddns__LocalRecords local_records;

		bool debug_active;
		napc_size debug_log_handler_index;

		napc__Timer debug_print_timer;
		napc__Timer network_advertisement_timer;
		napc__Timer statistics_timer;

		/**
		 * UDP Sockets
		 */
		napc__UDPSocket dns_udp_in;
		napc__UDPSocket networking_udp_out;
		napc__UDPSocket api_udp_in;

		/**
		 * Queries
		 */
		ddns__Query queries[32];

		/**
		 * API
		 */
		struct {
			bool random_iv_ready;
			napc_u8 random_iv[16];
		} api;

		/**
		 * Statistics
		 */
		struct {
			napc_u32 incoming_queries;
			napc_u32 completed_queries;
			napc_u32 truncated_responses;
			napc_u32 timeout_queries;

			napc_u16 _current_ticks_count;
			napc_u16 _current_queries_count;

			napc_u16 ticks_per_second;
			napc_u16 queries_per_second;

			napc_u16 avg_upstream_latency;

			napc_u16 tracked_metric_data[256];
		} stats;

		/**
		 * Shared buffers
		 */
		char buffer_1k_1[1024];
		bool buffer_1k_1_busy;

		char buffer_1k_2[1024];
		bool buffer_1k_2_busy;
	} ddns__Instance;

	void ddns_setup(
		ddns__Instance *instance,
		const char *config_file_path,
		const char *records_file_path
	);

	void ddns_loop(ddns__Instance *instance);
#endif
