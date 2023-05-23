//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
// Standard
#include <stdbool.h>
#include <stdint.h>

// Astrocast
#include "astronode_definitions.h"
#include "astronode_transport.h"
#include "device_interface.h"


//------------------------------------------------------------------------------
// Definitions
//------------------------------------------------------------------------------
// STX + OPCODE + Parameters + CRC + ETX
#define ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES ( 1 + \
                                                2 + \
                                                2 * ASTRONODE_APP_MSG_MAX_LEN_BYTES + \
                                                4 + \
                                                1)


//------------------------------------------------------------------------------
// Global variable definitions
//------------------------------------------------------------------------------
static const uint8_t g_ascii_lookup[16] =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

static uint16_t g_it_rx_buffer_length = 0;
static uint8_t g_it_rx_buffer[ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES] = {0};
static bool g_it_rx_complete = false;
static uint32_t g_it_rx_timeout_value = 0;


//------------------------------------------------------------------------------
// Static function declarations
//------------------------------------------------------------------------------
static bool ascii_to_value(uint8_t ascii, uint8_t *p_value);
#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
static as_return_status_t receive_astronode_answer(uint8_t *p_rx_buffer, uint16_t *p_buffer_length);
#endif /* ASTRONODE_TRANSPORT_BLOCKING_MODE */
static uint16_t astronode_create_request_transport(const astronode_app_msg_t *p_source_message, uint8_t *p_destination_buffer);
static as_return_status_t astronode_decode_answer_transport(uint8_t *p_source_buffer, uint16_t length_buffer, astronode_app_msg_t *p_destination_message);
static uint16_t calculate_crc(const uint8_t *p_data, uint16_t data_len, uint16_t init_value);
static void uint8_to_ascii_buffer(uint8_t value, uint8_t *p_target_buffer);


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------
#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_transport_send_receive(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer)
{
    uint8_t request_transport[ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES] = {0};
    uint8_t answer_transport[ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES] = {0};
    uint16_t answer_length =  0;

    uint16_t request_length = astronode_create_request_transport(p_request, request_transport);

    if (di_uart_astronode_write(request_transport, request_length) != RS_SUCCESS)
    {
        return RS_ASSET_FAILURE;
    }

    if(receive_astronode_answer(answer_transport, &answer_length) == RS_ASSET_SUCCESS)
    {
        return astronode_decode_answer_transport(answer_transport, answer_length, p_answer);
    }
    else
    {
        return RS_ASSET_FAILURE;
    }
}
#endif /* ASTRONODE_TRANSPORT_BLOCKING_MODE */

#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_transport_send(const astronode_app_msg_t *p_request)
{
    uint8_t request_transport[ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES] = {0};

    uint16_t request_length = astronode_create_request_transport(p_request, request_transport);

    g_it_rx_timeout_value = di_clock_get_system_tick();

    return (di_uart_astronode_write(request_transport, request_length) == RS_SUCCESS) ? RS_ASSET_SUCCESS : RS_ASSET_FAILURE;
}

void astronode_transport_it_receive_char_handler(uint8_t rx_char)
{
    if (rx_char == ASTRONODE_TRANSPORT_STX)
    {
        g_it_rx_buffer_length = 0;
        g_it_rx_complete = false;
    }

    if (g_it_rx_buffer_length < ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES)
    {
        g_it_rx_buffer[g_it_rx_buffer_length] = rx_char;
    }
    g_it_rx_buffer_length++;    // continue increasing the counter to indicate an overflow

    if (rx_char == ASTRONODE_TRANSPORT_ETX)
    {
        g_it_rx_complete = true;
    }
}

as_return_status_t astronode_transport_receive(astronode_app_msg_t *p_answer)
{
    if (g_it_rx_complete == true)
    {
        if (g_it_rx_buffer_length > ASTRONODE_TRANSPORT_MSG_MAX_LEN_BYTES)
        {
            g_it_rx_buffer_length = 0;
            g_it_rx_complete = false;
            return RS_ASSET_FAILURE;
        }
        return astronode_decode_answer_transport(g_it_rx_buffer, g_it_rx_buffer_length, p_answer);
    }
    else
    {
        if (di_clock_is_systick_timeout_over(g_it_rx_timeout_value, ASTRONODE_ANSWER_TIMEOUT_MS))
        {
            g_it_rx_buffer_length = 0;
            g_it_rx_complete = false;
            return RS_ASSET_TIMEOUT;
        }
        return RS_ASSET_BUSY;
    }
}
#endif /* ASTRONODE_TRANSPORT_ASYNC_MODE */

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
static as_return_status_t receive_astronode_answer(uint8_t *p_rx_buffer, uint16_t *p_buffer_length)
{
    uint8_t rx_char = 0;
    uint16_t length = 0;
    uint32_t timeout_answer_received = di_clock_get_system_tick();
    bool is_answer_received = false;

    while (is_answer_received == false)
    {
        if (di_clock_is_systick_timeout_over(timeout_answer_received, ASTRONODE_ANSWER_TIMEOUT_MS))
        {
            return RS_ASSET_TIMEOUT;
        }
        if (di_uart_astronode_receive_char(&rx_char) == RS_SUCCESS)
        {
            if (rx_char == ASTRONODE_TRANSPORT_STX)
            {
                is_answer_received = false;
                length = 0;
            }

            p_rx_buffer[length] = rx_char;
            length++;

            if (length > ASTRONODE_MAX_LENGTH_RESPONSE)
            {
                // ERROR : Message received from the Astronode exceed maximum length allowed.
                return RS_ASSET_FAILURE;
            }

            if (rx_char == ASTRONODE_TRANSPORT_ETX)
            {
                if (length > 1)
                {
                    *p_buffer_length = length;
                    is_answer_received = true;
                }
            }
        }
    }
    return RS_ASSET_SUCCESS;
}
#endif /* ASTRONODE_TRANSPORT_BLOCKING_MODE */

static uint16_t astronode_create_request_transport(const astronode_app_msg_t *p_source_message, uint8_t *p_destination_buffer)
{
    uint16_t index = 0;

    p_destination_buffer[index++] = ASTRONODE_TRANSPORT_STX;

    uint16_t crc = calculate_crc((const uint8_t *)&p_source_message->op_code, 1, 0xFFFF);
    crc = calculate_crc((const uint8_t *)&p_source_message->p_payload, p_source_message->payload_len, crc);
    crc = ((crc << 8) & 0xff00) | ((crc >> 8) & 0x00ff);

    uint8_to_ascii_buffer(p_source_message->op_code, &p_destination_buffer[index]);
    index += 2;

    for (uint16_t i = 0; i < p_source_message->payload_len; i++)
    {
        uint8_to_ascii_buffer(p_source_message->p_payload[i], &p_destination_buffer[index]);
        index += 2;
    }

    uint8_to_ascii_buffer(crc >> 8, &p_destination_buffer[index]);
    index += 2;
    uint8_to_ascii_buffer(crc & 0xFF, &p_destination_buffer[index]);
    index += 2;

    p_destination_buffer[index++] = ASTRONODE_TRANSPORT_ETX;

    return index;
}

static as_return_status_t astronode_decode_answer_transport(uint8_t *p_source_buffer, uint16_t length_buffer, astronode_app_msg_t *p_destination_message)
{
    if (p_source_buffer[0] != ASTRONODE_TRANSPORT_STX)
    {
        // ERROR : Message received from the Astronode does not start with STX character.
        return RS_ASSET_FAILURE;
    }

    if (length_buffer % 2 == 1 || length_buffer < 8) // 8: STX, ETX, 2 x opcode, 4 x CRC
    {
        // ERROR : Message received from the Astronode is missing at least one character.
        return RS_ASSET_FAILURE;
    }

    p_destination_message->payload_len = (length_buffer - 8) / 2;

    if (p_source_buffer[length_buffer - 1] != ASTRONODE_TRANSPORT_ETX)
    {
        // ERROR : Message received from the Astronode does not end with ETX character.
        return RS_ASSET_FAILURE;
    }

    uint8_t nibble_high = 0;
    uint8_t nibble_low = 0;

    // Op code
    if (ascii_to_value(p_source_buffer[1], &nibble_high) == false
        || ascii_to_value(p_source_buffer[2], &nibble_low) == false)
    {
        // ERROR : Message received from the Astronode contains a non-ASCII character.
        return RS_ASSET_FAILURE;
    }

    p_destination_message->op_code = (nibble_high << 4) + nibble_low;

    // Payload
    for (uint16_t i = 3, j = 0; i < length_buffer - 5; i += 2)
    {
        if (ascii_to_value(p_source_buffer[i], &nibble_high) == false
            || ascii_to_value(p_source_buffer[i + 1], &nibble_low) == false)
        {
           // ERROR : Message received from the Astronode contains a non-ASCII character.
            return RS_ASSET_FAILURE;
        }

        p_destination_message->p_payload[j++] = (nibble_high << 4) + nibble_low;
    }

    // CRC
    uint16_t crc_calculated = calculate_crc((const uint8_t *)&p_destination_message->op_code, 1, 0xFFFF);
    crc_calculated = calculate_crc((const uint8_t *)&p_destination_message->p_payload, p_destination_message->payload_len, crc_calculated);
    crc_calculated = ((crc_calculated << 8) & 0xff00) | ((crc_calculated >> 8) & 0x00ff);


    if (ascii_to_value(p_source_buffer[length_buffer - 5], &nibble_high) == false
        || ascii_to_value(p_source_buffer[length_buffer - 4], &nibble_low) == false)
    {
        // ERROR : Message received from the Astronode contains a non-ASCII character.
        return RS_ASSET_FAILURE;
    }

    uint16_t crc_received = (nibble_high << 12) + (nibble_low << 8);

    if (ascii_to_value(p_source_buffer[length_buffer - 3], &nibble_high) == false
        || ascii_to_value(p_source_buffer[length_buffer - 2], &nibble_low) == false)
    {
        // ERROR : Message received from the Astronode contains a non-ASCII character.
        return RS_ASSET_FAILURE;
    }

    crc_received += (nibble_high << 4) + nibble_low;

    if (crc_received != crc_calculated)
    {
       // ERROR : CRC sent by the Astronode does not match the expected CRC
        return RS_ASSET_CRC_ERROR;
    }

    return RS_ASSET_SUCCESS;
}

static uint16_t calculate_crc(const uint8_t *p_data, uint16_t data_len, uint16_t init_value)
{
    uint16_t crc = init_value;

    while (data_len--)
    {
        uint16_t x = crc >> 8 ^ *p_data++;
        x ^= x >> 4;
        crc = (crc << 8) ^ (x << 12) ^ (x << 5) ^ (x);
    }
    return crc;
}

static bool ascii_to_value(uint8_t ascii, uint8_t *p_value)
{
    if (ascii >= '0' && ascii <= '9')
    {
        *p_value = ascii - '0';
        return true;
    }
    else if (ascii >= 'A' && ascii <= 'F')
    {
        *p_value = ascii - 'A' + 10;
        return true;
    }
    else
    {
        return false;
    }
}

static void uint8_to_ascii_buffer(uint8_t value, uint8_t *p_target_buffer)
{
    p_target_buffer[0] = g_ascii_lookup[value >> 4];
    p_target_buffer[1] = g_ascii_lookup[value & 0x0F];
}