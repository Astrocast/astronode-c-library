//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
// Standard
#include <stdint.h>

// Third pary
#include <unity.h>
#include "fff.h"

// Astrocast
#include "astronode_application.c"

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
DEFINE_FFF_GLOBALS;


//------------------------------------------------------------------------------
// Global variable definitions
//------------------------------------------------------------------------------
static astronode_app_msg_t g_fake_transport_answer;


//------------------------------------------------------------------------------
// Static function declarations
//------------------------------------------------------------------------------
/**
 * @brief Add Type, Length, Value information to a target buffer.
 * @param p_target_buffer TLV bytes are placed in this target buffer.
 * @param p_value pointer to value. e.g. 4 bytes if uint32_t.
 * @param type value describing the data type. Usually pc_counter_id_t in this file.
 * @param length of data in bytes
 * @return total length of new TLV data
 */
static uint8_t add_tlv_to_buffer(uint8_t *p_target_buffer, uint8_t *p_value, uint8_t type, uint8_t length);


//------------------------------------------------------------------------------
// Fake functions
//------------------------------------------------------------------------------
FAKE_VALUE_FUNC(as_return_status_t, astronode_transport_send_receive, const astronode_app_msg_t *, astronode_app_msg_t *);
FAKE_VALUE_FUNC(as_return_status_t, astronode_transport_send, const astronode_app_msg_t *);
FAKE_VALUE_FUNC(as_return_status_t, astronode_transport_receive, astronode_app_msg_t *);
as_return_status_t astronode_transport_send_receive_custom_fake_only_opcode(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer);
as_return_status_t astronode_transport_send_receive_custom_fake_configuration_r(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer);
as_return_status_t astronode_transport_send_receive_custom_fake_global_answer(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer);
as_return_status_t astronode_transport_receive_custom_fake_wifi_wa(astronode_app_msg_t *p_answer);
as_return_status_t astronode_transport_send_receive_custom_fake_cfg_r_error(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer);
as_return_status_t astronode_transport_send_receive_custom_fake_perf_counters_r(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer);


//------------------------------------------------------------------------------
// Static function definitions
//------------------------------------------------------------------------------
as_return_status_t astronode_transport_send_receive_custom_fake_only_opcode(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer)
{
    p_answer->op_code = p_request->op_code + 0x80;
    return RS_ASSET_SUCCESS;
}

as_return_status_t astronode_transport_send_receive_custom_fake_configuration_r(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer)
{
    if (p_request->op_code != 0x15)
    {
        return RS_ASSET_FAILURE;
    }
    p_answer->op_code = 0x95;
    // product id: 3
    // hardware revision: 1
    // firmware major version: 2
    // firmware minor version: 1
    // firmware revision: 0
    // payload ack: 1
    // add geolocation: 0
    // ephemeris enabled: 1
    // deep sleep enabled: 0
    // payloack ack evt pin mask enabled: 1
    // reset notification evt pin mask enabled: 0
    // command avaiable evt pin mask enabled: 0
    // message pending evt pin mask enabled: 0
    uint8_t ans[8] = {0x03, 0x01, 0x02, 0x01, 0x00, 0x05, 0x00, 0x01};
    memcpy(p_answer->p_payload, ans, 8);
    p_answer->payload_len =8;
    return RS_ASSET_SUCCESS;
}

as_return_status_t astronode_transport_send_receive_custom_fake_global_answer(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer)
{
    memcpy(p_answer, &g_fake_transport_answer, sizeof(astronode_app_msg_t));

    return RS_ASSET_SUCCESS;
}

as_return_status_t astronode_transport_receive_custom_fake_wifi_wa(astronode_app_msg_t *p_answer)
{
    p_answer->op_code = ASTRONODE_OP_CODE_WIF_WA;
    p_answer->p_payload[0] = 123;
    return RS_ASSET_SUCCESS;
}

as_return_status_t astronode_transport_send_receive_custom_fake_cfg_r_error(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer)
{
    p_answer->op_code = ASTRONODE_OP_CODE_ERROR;
    p_answer->p_payload[0] = ASTRONODE_ERR_CODE_DUPLICATE_ID & 0xFF;
    p_answer->p_payload[1] = (ASTRONODE_ERR_CODE_DUPLICATE_ID >> 8) & 0xFF;
    return RS_ASSET_SUCCESS;
}

as_return_status_t astronode_transport_send_receive_custom_fake_perf_counters_r(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer)
{
    if (p_request->op_code != 0x67)
    {
        return RS_ASSET_FAILURE;
    }
    p_answer->op_code = 0xE7;

    p_answer->payload_len = 0;

    for (int type = 1; type < 15; type++)
    {
        uint32_t value =  0xF0 | type;
        p_answer->payload_len += add_tlv_to_buffer(&p_answer->p_payload[p_answer->payload_len], (uint8_t *) &value, type, 4);
    }

    return RS_ASSET_SUCCESS;
}


//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------
static uint8_t add_tlv_to_buffer(uint8_t *p_target_buffer, uint8_t *p_value, uint8_t type, uint8_t length)
{
    p_target_buffer[0] = type;
    p_target_buffer[1] = length;
    memcpy(&p_target_buffer[2], p_value, length);
    return (2 + length);
}

//------------------------------------------------------------------------------
// Test function declarations
//------------------------------------------------------------------------------
static void reset_fakes(void);


//------------------------------------------------------------------------------
// Unity function definitions
//------------------------------------------------------------------------------
void setUp(void)
{
    reset_fakes();
}

void tearDown(void)
{
}


//------------------------------------------------------------------------------
// Test function definitions
//------------------------------------------------------------------------------
static void reset_fakes(void)
{
    RESET_FAKE(astronode_transport_send_receive);
    RESET_FAKE(astronode_transport_send);
}

void test_error_codes(void)
{
    configuration_save_response_t ans = {.error = 0};

    // Asset's side errors : RS_ASSET_CRC_ERROR, RS_ASSET_TIMEOUT, RS_ASSET_FAILURE,
    astronode_transport_send_receive_fake.return_val = RS_ASSET_CRC_ERROR;

    as_return_status_t ret_status = astronode_request_configuration_save(&ans);
    TEST_ASSERT_EQUAL(RS_ASSET_CRC_ERROR, ret_status);
    TEST_ASSERT_EQUAL(0, ans.error);

    // Astronode's side error: RS_ASTRONODE_FAILURE
    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_cfg_r_error;
    ret_status = astronode_request_configuration_save(&ans);

    TEST_ASSERT_EQUAL(RS_ASTRONODE_FAILURE, ret_status);
    TEST_ASSERT_EQUAL(ASTRONODE_ERR_CODE_DUPLICATE_ID, ans.error);
}

void test_astronode_request_wifi_w(void)
{
    wifi_w_response_t ans;
    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_only_opcode;
    uint8_t wlan_ssid[ASTRONODE_WLAN_SSID_MAX_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x73, 0x73,0x69, 0x64};
    uint8_t wlan_key[ASTRONODE_WLAN_KEY_MAX_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x70, 0x61,0x73, 0x73, 0x77, 0x6F, 0x72, 0x64};
    uint8_t auth_token[ASTRONODE_AUTH_TOKEN_MAX_LENGTH] = {0x36, 0x6E, 0x78, 0x47, 0x52, 0x34, 0x65, 0x57, 0x59, 0x62, 0x34, 0x52, 0x38, 0x66, 0x45, 0x73, 0x58, 0x78, 0x32, 0x68, 0x31, 0x68, 0x47, 0x6F, 0x52, 0x36, 0x6E, 0x76, 0x6B, 0x75, 0x32, 0x54, 0x76, 0x47, 0x76, 0x54, 0x75, 0x46, 0x7A, 0x78, 0x69, 0x47, 0x59, 0x50, 0x70, 0x49, 0x43, 0x41, 0x41, 0x72, 0x6F, 0x5A, 0x4B, 0x74, 0x74, 0x48, 0x6E, 0x7A, 0x58, 0x54, 0x51, 0x53, 0x4C, 0x45, 0x69, 0x6C, 0x76, 0x43, 0x54, 0x54, 0x37, 0x72, 0x37, 0x45, 0x37, 0x75, 0x72, 0x5A, 0x37, 0x69, 0x45, 0x57, 0x34, 0x32, 0x66, 0x64, 0x69, 0x62, 0x6D, 0x58, 0x47, 0x34, 0x52, 0x4F, 0x51, 0x7A};

    as_return_status_t ret_status = astronode_request_wifi_w(&ans, wlan_ssid, wlan_key, auth_token);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = ASTRONODE_OP_CODE_WIF_WR;   // byte 0..3 of the structure
    call_args.payload_len = 194; // byte 198 of the structure
    memcpy(&call_args.p_payload[0], wlan_ssid, ASTRONODE_WLAN_SSID_MAX_LENGTH);
    memcpy(&call_args.p_payload[33], wlan_key, ASTRONODE_WLAN_KEY_MAX_LENGTH);
    memcpy(&call_args.p_payload[97], auth_token, ASTRONODE_AUTH_TOKEN_MAX_LENGTH);
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Verify deserialized response data
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
    TEST_ASSERT_EQUAL(ASTRONODE_OP_CODE_WIF_WA, ans.data.opcode);
}

void test_astronode_send_async_wifi_w(void)
{
    astronode_transport_send_fake.return_val = RS_ASSET_SUCCESS;
    uint8_t wlan_ssid[ASTRONODE_WLAN_SSID_MAX_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x73, 0x73,0x69, 0x64};
    uint8_t wlan_key[ASTRONODE_WLAN_KEY_MAX_LENGTH] = {0x6D, 0x79, 0x5F, 0x77, 0x69, 0x66, 0x69, 0x5F, 0x70, 0x61,0x73, 0x73, 0x77, 0x6F, 0x72, 0x64};
    uint8_t auth_token[ASTRONODE_AUTH_TOKEN_MAX_LENGTH] = {0x36, 0x6E, 0x78, 0x47, 0x52, 0x34, 0x65, 0x57, 0x59, 0x62, 0x34, 0x52, 0x38, 0x66, 0x45, 0x73, 0x58, 0x78, 0x32, 0x68, 0x31, 0x68, 0x47, 0x6F, 0x52, 0x36, 0x6E, 0x76, 0x6B, 0x75, 0x32, 0x54, 0x76, 0x47, 0x76, 0x54, 0x75, 0x46, 0x7A, 0x78, 0x69, 0x47, 0x59, 0x50, 0x70, 0x49, 0x43, 0x41, 0x41, 0x72, 0x6F, 0x5A, 0x4B, 0x74, 0x74, 0x48, 0x6E, 0x7A, 0x58, 0x54, 0x51, 0x53, 0x4C, 0x45, 0x69, 0x6C, 0x76, 0x43, 0x54, 0x54, 0x37, 0x72, 0x37, 0x45, 0x37, 0x75, 0x72, 0x5A, 0x37, 0x69, 0x45, 0x57, 0x34, 0x32, 0x66, 0x64, 0x69, 0x62, 0x6D, 0x58, 0x47, 0x34, 0x52, 0x4F, 0x51, 0x7A};

    as_return_status_t ret_status = astronode_send_async_wifi_w(wlan_ssid, wlan_key, auth_token);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
    // astronode_transport_send_fake.arg0_val can't be verified. request variable is non static.
}

void test_astronode_poll_answer_wifi_w(void)
{

    // Answer not received
    wifi_w_response_t struct_answer = {.error = 0};
    astronode_transport_receive_fake.return_val = RS_ASSET_BUSY;

    as_return_status_t ret_status = astronode_poll_answer_wifi_w(&struct_answer);

    TEST_ASSERT_EQUAL(1, astronode_transport_receive_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_BUSY, ret_status);
    TEST_ASSERT_EQUAL(0, struct_answer.error);

    // Answer received
    astronode_transport_receive_fake.custom_fake = astronode_transport_receive_custom_fake_wifi_wa;

    ret_status = astronode_poll_answer_wifi_w(&struct_answer);

    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
    TEST_ASSERT_EQUAL(ASTRONODE_OP_CODE_WIF_WA, struct_answer.data.opcode);
}

void test_astronode_request_configuration_w(void)
{
    configuration_w_response_t ans = {.error = 0};
    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_only_opcode;

    as_return_status_t ret_status = astronode_request_configuration_w(&ans, 1, 1, 0, 0, 1, 1, 0, 1);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = ASTRONODE_OP_CODE_CFG_WR;
    call_args.payload_len = 3;
    call_args.p_payload[0] = 0x03;
    call_args.p_payload[1] = 0x00;
    call_args.p_payload[2] = 0x0B;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Verify deserialized response data
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
}

void test_astronode_send_async_configuration_w(void)
{
    configuration_w_response_t ans = {.error = 0};
    astronode_transport_send_fake.return_val = RS_ASSET_SUCCESS;

    as_return_status_t ret_status = astronode_send_async_configuration_w(1, 1, 0, 0, 1, 1, 0, 1);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
}

void test_astronode_request_configuration_r(void)
{
    configuration_r_response_t ans = {.error = 0};
    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_configuration_r;

    as_return_status_t ret_status = astronode_request_configuration_r(&ans);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = 0x15;
    call_args.payload_len = 0;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Verify deserialized response data
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
//    TEST_ASSERT_EQUAL_HEX8(0x95, ans.data.opcode);
//    TEST_ASSERT_EQUAL(0, ans.error_code);
    TEST_ASSERT_EQUAL(3, ans.data.id);
    TEST_ASSERT_EQUAL(1, ans.data.hw_rev);
    TEST_ASSERT_EQUAL(2, ans.data.fw_major_v);
    TEST_ASSERT_EQUAL(1, ans.data.fw_minor_v);
    TEST_ASSERT_EQUAL(0, ans.data.fw_rev_v);
    TEST_ASSERT_EQUAL(1, ans.data.sat_ack);
    TEST_ASSERT_EQUAL(0, ans.data.geolocation);
    TEST_ASSERT_EQUAL(1, ans.data.ephemeris);
    TEST_ASSERT_EQUAL(0, ans.data.deep_sleep);
    TEST_ASSERT_EQUAL(1, ans.data.sat_ack_mask);
    TEST_ASSERT_EQUAL(0, ans.data.reset_notification_mask);
    TEST_ASSERT_EQUAL(0, ans.data.cmd_available_mask);
    TEST_ASSERT_EQUAL(0, ans.data.busy_mask);
}

void test_astronode_request_configuration_save(void)
{
    configuration_save_response_t ans = {.error = 0};

    astronode_request_configuration_save(&ans);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = 0x10;
    call_args.payload_len = 0;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Since it's generated code, the return structure test does not add value.
}

void test_astronode_request_configuration_reset(void)
{
    configuration_reset_response_t ans = {.error = 0};

    astronode_request_configuration_reset(&ans);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = 0x11;
    call_args.payload_len = 0;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Since it's generated code, the return structure test does not add value.
}

void test_astronode_request_payload_w(void)
{
    payload_w_response_t ans = {0};
    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_global_answer;
    g_fake_transport_answer.op_code = 0xA5;
    g_fake_transport_answer.payload_len = 2;
    g_fake_transport_answer.p_payload[0] = 0xab;
    g_fake_transport_answer.p_payload[1] = 0xcd;

    as_return_status_t ret_status = astronode_request_payload_w(&ans, 0x3e9, "Test", 4);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = 0x25;
    call_args.p_payload[0] = 0xE9;
    call_args.p_payload[1] = 0x03;
    memcpy(&call_args.p_payload[2], "Test", 4);
    call_args.payload_len = 6;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Verify deserialized response data
    TEST_ASSERT_EQUAL(0xcdab, ans.data.counter);     // 0xcdab is returned by astronode_transport_send_receive_custom_fake_global_answer

    memset(&g_fake_transport_answer, 0, sizeof(astronode_app_msg_t));
}

void test_astronode_request_payload_dequeue(void)
{

}

void test_astronode_request_payload_clear(void)
{

}

void test_astronode_request_geolocation_w(void)
{
    geolocation_w_response_t ans = {.error = 0};

    astronode_request_geolocation_w(&ans, 465343400, 65787470);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = 0x35;   // byte 0..3 of the structure 
    call_args.payload_len = 8; // byte 198 of the structure
    call_args.p_payload[0] = 0xA8;  // byte 4 of the structure
    call_args.p_payload[1] = 0x93;
    call_args.p_payload[2] = 0xBC;
    call_args.p_payload[3] = 0x1B;
    call_args.p_payload[4] = 0x4E;
    call_args.p_payload[5] = 0xD6;
    call_args.p_payload[6] = 0xEb;
    call_args.p_payload[7] = 0x03;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));
    // Since it's generated code, the return structure test does not add value.
}

void test_astronode_request_event_r(void)
{
    event_r_response_t ans = {0};
    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_global_answer;
    g_fake_transport_answer.op_code = 0xE5;
    g_fake_transport_answer.payload_len = 1;
    g_fake_transport_answer.p_payload[0] = 0x05; // sat_ack and cmd_available are set. Module_reset and message_pending are not set

    as_return_status_t ret_status = astronode_request_event_r(&ans);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = 0x65;
    call_args.payload_len = 0;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Verify deserilized response data
    TEST_ASSERT_EQUAL(1, ans.data.sak);
    TEST_ASSERT_EQUAL(0, ans.data.reset);
    TEST_ASSERT_EQUAL(1, ans.data.cmd);
    TEST_ASSERT_EQUAL(0, ans.data.busy);

    memset(&g_fake_transport_answer, 0, sizeof(astronode_app_msg_t));
}

void test_astronode_request_sak_r(void)
{

}

void test_astronode_request_sak_cl(void)
{

}

void test_astronode_request_reset_cl(void)
{

}

void test_astronode_request_cmd_r(void)
{
    cmd_r_response_t ans = {.error = 0};
    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_global_answer;
    g_fake_transport_answer.op_code = 0xC7;
    const uint8_t CREATED_DATE_SIZE = 4;
    const uint8_t COMMAND_SIZE = 8;
    uint32_t created_date = 0x12345678;
    memcpy(&g_fake_transport_answer.p_payload[0], &created_date, CREATED_DATE_SIZE); // bytes 0..3 are the created date
    uint8_t command_8bytes[8] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xAA, 0xAB};
    memcpy(&g_fake_transport_answer.p_payload[CREATED_DATE_SIZE], command_8bytes, COMMAND_SIZE);
    g_fake_transport_answer.payload_len = CREATED_DATE_SIZE + COMMAND_SIZE;

    as_return_status_t ret_status = astronode_request_cmd_r(&ans);
    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);

    // Verify serialized request data
    astronode_app_msg_t call_args = {0};
    call_args.op_code = 0x47;
    call_args.payload_len = 0;
    TEST_ASSERT_EQUAL_MEMORY(&call_args, astronode_transport_send_receive_fake.arg0_val, sizeof(astronode_app_msg_t));

    // Verify deserilized response data
    TEST_ASSERT_EQUAL_UINT32(created_date, ans.data.created_date);
    TEST_ASSERT_EQUAL(COMMAND_SIZE, ans.data.cmd_len);
    TEST_ASSERT_EQUAL_MEMORY(command_8bytes, ans.data.cmd, COMMAND_SIZE);

    memset(&g_fake_transport_answer, 0, sizeof(astronode_app_msg_t));
}

void test_astronode_request_cmd_cl(void)
{

}

void test_astronode_request_rtc_r(void)
{

}

void test_astronode_request_guid_r(void)
{

}

void test_astronode_request_sn_r(void)
{

}

void test_astronode_request_pn_r(void)
{

}

void test_astronode_request_eph_r(void)
{

}

void test_astronode_request_context_save(void)
{

}

void test_astronode_request_perf_counters_r(void)
{
    perf_counters_r_response_t ans = {0}; //{.error = 0};

    astronode_transport_send_receive_fake.custom_fake = astronode_transport_send_receive_custom_fake_perf_counters_r;

    as_return_status_t ret_status = astronode_request_perf_counters_r(&ans);

    TEST_ASSERT_EQUAL(1, astronode_transport_send_receive_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
    TEST_ASSERT_EQUAL(ASTRONODE_OP_CODE_PER_RA, ans.data.opcode);
    TEST_ASSERT_EQUAL(0xF1, ans.data.sat_search_phase);
    TEST_ASSERT_EQUAL(0xF2, ans.data.sat_search_try);
    TEST_ASSERT_EQUAL(0xF3, ans.data.sat_demod_phase);
    TEST_ASSERT_EQUAL(0xF4, ans.data.sat_demod_try);
    TEST_ASSERT_EQUAL(0xF5, ans.data.valid_sat_demod);
    TEST_ASSERT_EQUAL(0xF6, ans.data.ack_demod_try);
    TEST_ASSERT_EQUAL(0xF7, ans.data.valid_ack_demod);
    TEST_ASSERT_EQUAL(0xF8, ans.data.msg_queued);
    TEST_ASSERT_EQUAL(0xF9, ans.data.msg_dequeued);
    TEST_ASSERT_EQUAL(0xFA, ans.data.msg_ack);
    TEST_ASSERT_EQUAL(0xFB, ans.data.fragment_tx);
    TEST_ASSERT_EQUAL(0xFC, ans.data.fragment_ack);
    TEST_ASSERT_EQUAL(0xFD, ans.data.unicast_demod_try);
    TEST_ASSERT_EQUAL(0xFE, ans.data.valid_unicast_demod);
}

void test_astronode_request_perf_counters_cl(void)
{

}

void test_astronode_request_module_state_r(void)
{

}

void test_astronode_request_last_contact_r(void)
{

}

void test_astronode_request_environment_r(void)
{

}

void test_astronode_request_config_sat_search(void)
{
    // TODO fill test with request values verification
}

// ------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_error_codes);
    RUN_TEST(test_astronode_request_wifi_w);
    RUN_TEST(test_astronode_send_async_wifi_w);
    RUN_TEST(test_astronode_poll_answer_wifi_w);
    RUN_TEST(test_astronode_request_configuration_w);
    RUN_TEST(test_astronode_send_async_configuration_w);
    RUN_TEST(test_astronode_request_configuration_r);
    RUN_TEST(test_astronode_request_configuration_save);
    RUN_TEST(test_astronode_request_configuration_reset);
    RUN_TEST(test_astronode_request_payload_w);
    RUN_TEST(test_astronode_request_payload_dequeue);
    RUN_TEST(test_astronode_request_payload_clear);
    RUN_TEST(test_astronode_request_geolocation_w);
    RUN_TEST(test_astronode_request_event_r);
    RUN_TEST(test_astronode_request_sak_r);
//    RUN_TEST(test_astronode_request_sak_cl);
//    RUN_TEST(test_astronode_request_reset_cl);
    RUN_TEST(test_astronode_request_cmd_r);
//    RUN_TEST(test_astronode_request_cmd_cl);
//    RUN_TEST(test_astronode_request_rtc_r);
//    RUN_TEST(test_astronode_request_guid_r);
//    RUN_TEST(test_astronode_request_sn_r);
//    RUN_TEST(test_astronode_request_pn_r);
//    RUN_TEST(test_astronode_request_eph_r);
//    RUN_TEST(test_astronode_request_context_save);
    RUN_TEST(test_astronode_request_perf_counters_r);
//    RUN_TEST(test_astronode_request_perf_counters_cl);
//    RUN_TEST(test_astronode_request_module_state_r);
//    RUN_TEST(test_astronode_request_last_contact_r);
//    RUN_TEST(test_astronode_request_environment_r);
//    RUN_TEST(test_astronode_request_config_sat_search);
    return UNITY_END();
}