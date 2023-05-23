//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
// Standard
#include <stdint.h>

// Third pary
#include <unity.h>
#include "fff.h"

// Astrocast
#include "astronode_transport.c"


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
DEFINE_FFF_GLOBALS;


//------------------------------------------------------------------------------
// Global variable definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Fake functions
//------------------------------------------------------------------------------
FAKE_VOID_FUNC(di_log_send, char *);
FAKE_VALUE_FUNC(return_status_t, di_uart_astronode_write, const uint8_t *, uint16_t);
FAKE_VALUE_FUNC(return_status_t, di_uart_astronode_receive_char, uint8_t *);
FAKE_VALUE_FUNC(uint32_t, di_clock_get_system_tick);
FAKE_VALUE_FUNC(bool, di_clock_is_systick_timeout_over, uint32_t, uint32_t);


//------------------------------------------------------------------------------
// Static functions definitions
//------------------------------------------------------------------------------
void receive_cfg_wa_frame(void);


//------------------------------------------------------------------------------
// Static functions definitions
//------------------------------------------------------------------------------
void receive_cfg_wa_frame(void)
{
    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_STX);
    astronode_transport_it_receive_char_handler(0x38);
    astronode_transport_it_receive_char_handler(0x35);
    astronode_transport_it_receive_char_handler(0x44);
    astronode_transport_it_receive_char_handler(0x44);
    astronode_transport_it_receive_char_handler(0x32);
    astronode_transport_it_receive_char_handler(0x30);
    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_ETX);
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
    RESET_FAKE(di_clock_is_systick_timeout_over);
    RESET_FAKE(di_uart_astronode_write);
    g_it_rx_complete = false;
    g_it_rx_buffer_length = 0;
}

void test_receive_astronode_answer(void)
{

}

void test_astronode_transport_send(void)
{
    di_uart_astronode_write_fake.return_val = RS_SUCCESS;
    astronode_app_msg_t request;
    request.op_code = 0x05;     // CFG_W
    request.payload_len = 3;
    request.p_payload[0] = 0x03;
    request.p_payload[1] = 0x00;
    request.p_payload[2] = 0x0B;

    as_return_status_t ans = astronode_transport_send(&request);

    TEST_ASSERT_EQUAL(1, di_uart_astronode_write_fake.call_count);
    TEST_ASSERT_EQUAL(RS_SUCCESS, di_uart_astronode_write_fake.return_val);
    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ans);
}

void test_astronode_transport_send_error(void)
{
    di_uart_astronode_write_fake.return_val = RS_FAILURE;
    astronode_app_msg_t request;
    request.op_code = 0x05;     // CFG_W
    request.payload_len = 3;
    request.p_payload[0] = 0x03;
    request.p_payload[1] = 0x00;
    request.p_payload[2] = 0x0B;

    as_return_status_t ans = astronode_transport_send(&request);

    TEST_ASSERT_EQUAL(1, di_uart_astronode_write_fake.call_count);
    TEST_ASSERT_EQUAL(RS_ASSET_FAILURE, ans);
}

void test_astronode_transport_it_receive_char_handler(void)
{
    uint16_t rx_buffer_index = 0;

    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_STX);
    TEST_ASSERT_EQUAL_UINT8(ASTRONODE_TRANSPORT_STX, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    // Receive CFG_WA
    astronode_transport_it_receive_char_handler(0x38);
    TEST_ASSERT_EQUAL_UINT8(0x38, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    astronode_transport_it_receive_char_handler(0x35);
    TEST_ASSERT_EQUAL_UINT8(0x35, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    astronode_transport_it_receive_char_handler(0x44);
    TEST_ASSERT_EQUAL_UINT8(0x44, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    astronode_transport_it_receive_char_handler(0x44);
    TEST_ASSERT_EQUAL_UINT8(0x44, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    astronode_transport_it_receive_char_handler(0x32);
    TEST_ASSERT_EQUAL_UINT8(0x32, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    astronode_transport_it_receive_char_handler(0x30);
    TEST_ASSERT_EQUAL_UINT8(0x30, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_ETX);
    TEST_ASSERT_EQUAL_UINT8(ASTRONODE_TRANSPORT_ETX, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_TRUE(g_it_rx_complete);

    // Receive new frame, counter should be reset
    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_STX);
    TEST_ASSERT_EQUAL(1, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    // Clear buffer
//    astronode_transport_it_receive_char_handler(0x38);
//    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_ETX);
//    TEST_ASSERT_TRUE(g_it_rx_complete);

}

void test_astronode_transport_it_receive_char_handler_bad_frame(void)
{
    uint16_t rx_buffer_index = 0;

    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_STX);
    TEST_ASSERT_EQUAL_UINT8(ASTRONODE_TRANSPORT_STX, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    // Receive CFG_WA
    astronode_transport_it_receive_char_handler(0x38);
    TEST_ASSERT_EQUAL_UINT8(0x38, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    astronode_transport_it_receive_char_handler(0x35);
    TEST_ASSERT_EQUAL_UINT8(0x35, g_it_rx_buffer[rx_buffer_index++]);
    TEST_ASSERT_EQUAL(rx_buffer_index, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    // Receive STX again
    astronode_transport_it_receive_char_handler(ASTRONODE_TRANSPORT_STX);
    TEST_ASSERT_EQUAL(1, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);
}

void test_astronode_transport_receive(void)
{
    as_return_status_t ret_status;
    astronode_app_msg_t answer = {0};
    const astronode_app_msg_t EMTPY_ANS = {0};

    // Nothing received
    ret_status = astronode_transport_receive(&answer);
    TEST_ASSERT_EQUAL(RS_ASSET_BUSY, ret_status);
    TEST_ASSERT_EQUAL_MEMORY(&answer, &EMTPY_ANS, sizeof(astronode_app_msg_t));

    // Answer received
    receive_cfg_wa_frame();

    ret_status = astronode_transport_receive(&answer);

    TEST_ASSERT_EQUAL(RS_ASSET_SUCCESS, ret_status);
    TEST_ASSERT_EQUAL(answer.op_code, ASTRONODE_OP_CODE_CFG_WA);
    TEST_ASSERT_EQUAL(answer.payload_len, 0);
    TEST_ASSERT_EQUAL_MEMORY(&answer.p_payload, &EMTPY_ANS, ASTRONODE_APP_MSG_MAX_LEN_BYTES);
}

void test_astronode_transport_receive_error(void)
{
    as_return_status_t ret_status;
    astronode_app_msg_t answer = {0};

    // Max size exceeded
    g_it_rx_buffer_length = ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES + 1;
    g_it_rx_complete = true;

    ret_status = astronode_transport_receive(&answer);

    TEST_ASSERT_EQUAL(RS_ASSET_FAILURE, ret_status);
    TEST_ASSERT_EQUAL(0, g_it_rx_buffer_length);
    TEST_ASSERT_FALSE(g_it_rx_complete);

    // buffer size too small, error detected by astronode_decode_answer_transport.
    g_it_rx_buffer_length = 1;
    g_it_rx_complete = true;

    ret_status = astronode_transport_receive(&answer);

    TEST_ASSERT_EQUAL(RS_ASSET_FAILURE, ret_status);
}

void test_astronode_transport_receive_timeout(void)
{
    as_return_status_t ret_status;
    astronode_app_msg_t answer = {0};
    g_it_rx_timeout_value = 0;
    // Timeout not raised
    di_clock_is_systick_timeout_over_fake.return_val = false;

    ret_status = astronode_transport_receive(&answer);

    TEST_ASSERT_EQUAL(RS_ASSET_BUSY, ret_status);

    // Timeout raised
    di_clock_is_systick_timeout_over_fake.return_val = true;

    ret_status = astronode_transport_receive(&answer);

    TEST_ASSERT_EQUAL(RS_ASSET_TIMEOUT, ret_status);
}

void test_astronode_create_request_transport(void)
{
}


// ------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_receive_astronode_answer);
    RUN_TEST(test_astronode_transport_send);
    RUN_TEST(test_astronode_transport_send_error);
    RUN_TEST(test_astronode_transport_send);
    RUN_TEST(test_astronode_transport_it_receive_char_handler);
    RUN_TEST(test_astronode_transport_it_receive_char_handler_bad_frame);
    RUN_TEST(test_astronode_transport_receive);
    RUN_TEST(test_astronode_transport_receive_error);
    RUN_TEST(test_astronode_transport_receive_timeout);

    RUN_TEST(test_astronode_create_request_transport);
    return UNITY_END();
}