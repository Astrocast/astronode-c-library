#ifdef __cplusplus
extern "C" {
#endif


// ------------------------------------------------------------------------------
// Includes 
// ------------------------------------------------------------------------------
// Standard
#include <stdbool.h>
#include <stdint.h>

// Astrocast 
#include "astronode_definitions.h"

/**
 * @info Automatically generated code.
 * @details Commands arguments definition can be found on Astrocast docs website.
 * @see https://docs.astrocast.com/docs/products/astronode-api/commands-definition
 */

 
// ------------------------------------------------------------------------------
// Functions declaration
// ------------------------------------------------------------------------------
typedef struct wifi_w_response_data
{
    uint8_t opcode;
} wifi_w_response_data_t;

typedef union wifi_w_response
{
    wifi_w_response_data_t data;
    astronode_error_code error;
} wifi_w_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_wifi_w(wifi_w_response_t *p_answer, const char *p_ssid, const char *p_wlan_key, const char *p_api_token);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_wifi_w(const char *p_ssid, const char *p_wlan_key, const char *p_api_token);
as_return_status_t astronode_poll_answer_wifi_w(wifi_w_response_t *p_answer);
#endif

typedef struct configuration_w_response_data
{
    uint8_t opcode;
} configuration_w_response_data_t;

typedef union configuration_w_response
{
    configuration_w_response_data_t data;
    astronode_error_code error;
} configuration_w_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_w(configuration_w_response_t *p_answer, bool sat_ack, bool geolocation, bool ephemeris, bool deep_sleep, bool sat_ack_mask, bool reset_notification_mask, bool cmd_available_mask, bool busy_mask);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_w(bool sat_ack, bool geolocation, bool ephemeris, bool deep_sleep, bool sat_ack_mask, bool reset_notification_mask, bool cmd_available_mask, bool busy_mask);
as_return_status_t astronode_poll_answer_configuration_w(configuration_w_response_t *p_answer);
#endif

typedef struct configuration_r_response_data
{
    uint8_t opcode;
    uint8_t id;
    uint8_t hw_rev;
    uint8_t fw_major_v;
    uint8_t fw_minor_v;
    uint8_t fw_rev_v;
    bool sat_ack;
    bool geolocation;
    bool ephemeris;
    bool deep_sleep;
    bool sat_ack_mask;
    bool reset_notification_mask;
    bool cmd_available_mask;
    bool busy_mask;
} configuration_r_response_data_t;

typedef union configuration_r_response
{
    configuration_r_response_data_t data;
    astronode_error_code error;
} configuration_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_r(configuration_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_r();
as_return_status_t astronode_poll_answer_configuration_r(configuration_r_response_t *p_answer);
#endif

typedef struct configuration_save_response_data
{
    uint8_t opcode;
} configuration_save_response_data_t;

typedef union configuration_save_response
{
    configuration_save_response_data_t data;
    astronode_error_code error;
} configuration_save_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_save(configuration_save_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_save();
as_return_status_t astronode_poll_answer_configuration_save(configuration_save_response_t *p_answer);
#endif

typedef struct configuration_reset_response_data
{
    uint8_t opcode;
} configuration_reset_response_data_t;

typedef union configuration_reset_response
{
    configuration_reset_response_data_t data;
    astronode_error_code error;
} configuration_reset_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_reset(configuration_reset_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_reset();
as_return_status_t astronode_poll_answer_configuration_reset(configuration_reset_response_t *p_answer);
#endif

typedef struct payload_w_response_data
{
    uint8_t opcode;
    uint16_t counter;
} payload_w_response_data_t;

typedef union payload_w_response
{
    payload_w_response_data_t data;
    astronode_error_code error;
} payload_w_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_payload_w(payload_w_response_t *p_answer, uint16_t counter, const char *p_payload, uint16_t payload_length);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_payload_w(uint16_t counter, const char *p_payload, uint16_t payload_length);
as_return_status_t astronode_poll_answer_payload_w(payload_w_response_t *p_answer);
#endif

typedef struct payload_dequeue_response_data
{
    uint8_t opcode;
    uint16_t counter;
} payload_dequeue_response_data_t;

typedef union payload_dequeue_response
{
    payload_dequeue_response_data_t data;
    astronode_error_code error;
} payload_dequeue_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_payload_dequeue(payload_dequeue_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_payload_dequeue();
as_return_status_t astronode_poll_answer_payload_dequeue(payload_dequeue_response_t *p_answer);
#endif

typedef struct payload_clear_response_data
{
    uint8_t opcode;
} payload_clear_response_data_t;

typedef union payload_clear_response
{
    payload_clear_response_data_t data;
    astronode_error_code error;
} payload_clear_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_payload_clear(payload_clear_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_payload_clear();
as_return_status_t astronode_poll_answer_payload_clear(payload_clear_response_t *p_answer);
#endif

typedef struct geolocation_w_response_data
{
    uint8_t opcode;
} geolocation_w_response_data_t;

typedef union geolocation_w_response
{
    geolocation_w_response_data_t data;
    astronode_error_code error;
} geolocation_w_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_geolocation_w(geolocation_w_response_t *p_answer, int32_t lat, int32_t lng);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_geolocation_w(int32_t lat, int32_t lng);
as_return_status_t astronode_poll_answer_geolocation_w(geolocation_w_response_t *p_answer);
#endif

typedef struct event_r_response_data
{
    uint8_t opcode;
    bool sak;
    bool reset;
    bool cmd;
    bool busy;
} event_r_response_data_t;

typedef union event_r_response
{
    event_r_response_data_t data;
    astronode_error_code error;
} event_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_event_r(event_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_event_r();
as_return_status_t astronode_poll_answer_event_r(event_r_response_t *p_answer);
#endif

typedef struct sak_r_response_data
{
    uint8_t opcode;
    uint16_t counter;
} sak_r_response_data_t;

typedef union sak_r_response
{
    sak_r_response_data_t data;
    astronode_error_code error;
} sak_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_sak_r(sak_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_sak_r();
as_return_status_t astronode_poll_answer_sak_r(sak_r_response_t *p_answer);
#endif

typedef struct sak_cl_response_data
{
    uint8_t opcode;
} sak_cl_response_data_t;

typedef union sak_cl_response
{
    sak_cl_response_data_t data;
    astronode_error_code error;
} sak_cl_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_sak_cl(sak_cl_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_sak_cl();
as_return_status_t astronode_poll_answer_sak_cl(sak_cl_response_t *p_answer);
#endif

typedef struct reset_cl_response_data
{
    uint8_t opcode;
} reset_cl_response_data_t;

typedef union reset_cl_response
{
    reset_cl_response_data_t data;
    astronode_error_code error;
} reset_cl_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_reset_cl(reset_cl_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_reset_cl();
as_return_status_t astronode_poll_answer_reset_cl(reset_cl_response_t *p_answer);
#endif

typedef struct cmd_r_response_data
{
    uint8_t opcode;
    uint32_t created_date;
    char cmd[ASTRONODE_MAX_LENGTH_RESPONSE];
    uint8_t cmd_len;
} cmd_r_response_data_t;

typedef union cmd_r_response
{
    cmd_r_response_data_t data;
    astronode_error_code error;
} cmd_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_cmd_r(cmd_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_cmd_r();
as_return_status_t astronode_poll_answer_cmd_r(cmd_r_response_t *p_answer);
#endif

typedef struct cmd_cl_response_data
{
    uint8_t opcode;
} cmd_cl_response_data_t;

typedef union cmd_cl_response
{
    cmd_cl_response_data_t data;
    astronode_error_code error;
} cmd_cl_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_cmd_cl(cmd_cl_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_cmd_cl();
as_return_status_t astronode_poll_answer_cmd_cl(cmd_cl_response_t *p_answer);
#endif

typedef struct rtc_r_response_data
{
    uint8_t opcode;
    uint32_t time;
} rtc_r_response_data_t;

typedef union rtc_r_response
{
    rtc_r_response_data_t data;
    astronode_error_code error;
} rtc_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_rtc_r(rtc_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_rtc_r();
as_return_status_t astronode_poll_answer_rtc_r(rtc_r_response_t *p_answer);
#endif

typedef struct guid_r_response_data
{
    uint8_t opcode;
    char guid[288];
    uint8_t guid_len;
} guid_r_response_data_t;

typedef union guid_r_response
{
    guid_r_response_data_t data;
    astronode_error_code error;
} guid_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_guid_r(guid_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_guid_r();
as_return_status_t astronode_poll_answer_guid_r(guid_r_response_t *p_answer);
#endif

typedef struct sn_r_response_data
{
    uint8_t opcode;
    char sn[128];
    uint8_t sn_len;
} sn_r_response_data_t;

typedef union sn_r_response
{
    sn_r_response_data_t data;
    astronode_error_code error;
} sn_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_sn_r(sn_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_sn_r();
as_return_status_t astronode_poll_answer_sn_r(sn_r_response_t *p_answer);
#endif

typedef struct pn_r_response_data
{
    uint8_t opcode;
    char pn[128];
    uint8_t pn_len;
} pn_r_response_data_t;

typedef union pn_r_response
{
    pn_r_response_data_t data;
    astronode_error_code error;
} pn_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_pn_r(pn_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_pn_r();
as_return_status_t astronode_poll_answer_pn_r(pn_r_response_t *p_answer);
#endif

typedef struct eph_r_response_data
{
    uint8_t opcode;
    uint32_t next_pass;
} eph_r_response_data_t;

typedef union eph_r_response
{
    eph_r_response_data_t data;
    astronode_error_code error;
} eph_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_eph_r(eph_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_eph_r();
as_return_status_t astronode_poll_answer_eph_r(eph_r_response_t *p_answer);
#endif

typedef struct context_save_response_data
{
    uint8_t opcode;
} context_save_response_data_t;

typedef union context_save_response
{
    context_save_response_data_t data;
    astronode_error_code error;
} context_save_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_context_save(context_save_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_context_save();
as_return_status_t astronode_poll_answer_context_save(context_save_response_t *p_answer);
#endif

typedef struct perf_counters_r_response_data
{
    uint8_t opcode;
    uint32_t sat_search_phase;
    uint32_t sat_search_try;
    uint32_t sat_demod_phase;
    uint32_t sat_demod_try;
    uint32_t valid_sat_demod;
    uint32_t ack_demod_try;
    uint32_t valid_ack_demod;
    uint32_t msg_queued;
    uint32_t msg_dequeued;
    uint32_t msg_ack;
    uint32_t fragment_tx;
    uint32_t fragment_ack;
    uint32_t unicast_demod_try;
    uint32_t valid_unicast_demod;
} perf_counters_r_response_data_t;

typedef union perf_counters_r_response
{
    perf_counters_r_response_data_t data;
    astronode_error_code error;
} perf_counters_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_perf_counters_r(perf_counters_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_perf_counters_r();
as_return_status_t astronode_poll_answer_perf_counters_r(perf_counters_r_response_t *p_answer);
#endif

typedef struct perf_counters_cl_response_data
{
    uint8_t opcode;
} perf_counters_cl_response_data_t;

typedef union perf_counters_cl_response
{
    perf_counters_cl_response_data_t data;
    astronode_error_code error;
} perf_counters_cl_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_perf_counters_cl(perf_counters_cl_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_perf_counters_cl();
as_return_status_t astronode_poll_answer_perf_counters_cl(perf_counters_cl_response_t *p_answer);
#endif

typedef struct module_state_r_response_data
{
    uint8_t opcode;
    uint8_t msg_queued;
    uint8_t ack_msg_queued;
    enum reset_reason_t    
    {
        no_reset = 0,
        power_on_reset = 1,
        software_reset = 2,
        watchdog_reset = 3,
        brown_out = 4,
    } reset_reason_t;
    enum reset_reason_t last_reset_reason;
    uint32_t uptime;
} module_state_r_response_data_t;

typedef union module_state_r_response
{
    module_state_r_response_data_t data;
    astronode_error_code error;
} module_state_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_module_state_r(module_state_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_module_state_r();
as_return_status_t astronode_poll_answer_module_state_r(module_state_r_response_t *p_answer);
#endif

typedef struct last_contact_r_response_data
{
    uint8_t opcode;
    uint32_t start_time;
    uint32_t end_time;
    uint8_t peak_rssi;
    uint32_t peak_time;
} last_contact_r_response_data_t;

typedef union last_contact_r_response
{
    last_contact_r_response_data_t data;
    astronode_error_code error;
} last_contact_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_last_contact_r(last_contact_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_last_contact_r();
as_return_status_t astronode_poll_answer_last_contact_r(last_contact_r_response_t *p_answer);
#endif

typedef struct environment_r_response_data
{
    uint8_t opcode;
    enum mac_result_t    
    {
        none = 0,
        success = 1,
        satdet_fail = 2,
        sync_demod_fail = 3,
        signaling_demod_fail = 4,
        ack_signaling_fail = 5,
        no_ack_in_sf = 6,
        error = 7,
        timeout = 8,
        blacklisted = 9,
        test_sat = 10,
        sat_low_power = 11,
    } mac_result_t;
    enum mac_result_t last_mac_result;
    uint8_t last_rssi;
    uint32_t time_since_satdet;
} environment_r_response_data_t;

typedef union environment_r_response
{
    environment_r_response_data_t data;
    astronode_error_code error;
} environment_r_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_environment_r(environment_r_response_t *p_answer);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_environment_r();
as_return_status_t astronode_poll_answer_environment_r(environment_r_response_t *p_answer);
#endif

typedef struct config_sat_search_response_data
{
    uint8_t opcode;
} config_sat_search_response_data_t;

typedef union config_sat_search_response
{
    config_sat_search_response_data_t data;
    astronode_error_code error;
} config_sat_search_response_t;

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_config_sat_search(config_sat_search_response_t *p_answer, uint8_t setting, bool search_wo_msg);
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_config_sat_search(uint8_t setting, bool search_wo_msg);
as_return_status_t astronode_poll_answer_config_sat_search(config_sat_search_response_t *p_answer);
#endif

#ifdef __cplusplus
}
#endif
