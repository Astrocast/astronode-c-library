// ------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------
// Standard
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
    
// Astrocast
#include "astronode_application.h"
#include "astronode_definitions.h"
#include "astronode_transport.h"

/**
 * @info Automatically generated code.
 * @details Commands arguments definition can be found on Astrocast docs website.
 * @see https://docs.astrocast.com/docs/products/astronode-api/commands-definition
 */
 

// ------------------------------------------------------------------------------
// Functions definition
// ------------------------------------------------------------------------------
//////////////////////////////////////////
// Command wifi_w
//////////////////////////////////////////
static void wifi_w_serialize(astronode_app_msg_t *p_serialized_data, const char *p_ssid, const char *p_wlan_key, const char *p_api_token)
{
    memcpy(&p_serialized_data->p_payload[0], p_ssid, 33);
    memcpy(&p_serialized_data->p_payload[33], p_wlan_key, 64);
    memcpy(&p_serialized_data->p_payload[97], p_api_token, 97);
    p_serialized_data->payload_len += 194;
}

static void wifi_w_deserialize(wifi_w_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_wifi_w(wifi_w_response_t *p_answer, const char *p_ssid, const char *p_wlan_key, const char *p_api_token)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x06;
    wifi_w_serialize(&request, p_ssid, p_wlan_key, p_api_token);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x86)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    wifi_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_wifi_w(const char *p_ssid, const char *p_wlan_key, const char *p_api_token)
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x06;
    wifi_w_serialize(&request, p_ssid, p_wlan_key, p_api_token);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_wifi_w(wifi_w_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x86)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    wifi_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command configuration_w
//////////////////////////////////////////
static void configuration_w_serialize(astronode_app_msg_t *p_serialized_data, bool sat_ack, bool geolocation, bool ephemeris, bool deep_sleep, bool sat_ack_mask, bool reset_notification_mask, bool cmd_available_mask, bool busy_mask)
{
    p_serialized_data->p_payload[0] = sat_ack | (geolocation << 1) | (ephemeris << 2) | (deep_sleep << 3);
    //padding:12 bits
    p_serialized_data->p_payload[2] = sat_ack_mask | (reset_notification_mask << 1) | (cmd_available_mask << 2) | (busy_mask << 3);
    //padding:4 bits
    p_serialized_data->payload_len += 3;
}

static void configuration_w_deserialize(configuration_w_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_w(configuration_w_response_t *p_answer, bool sat_ack, bool geolocation, bool ephemeris, bool deep_sleep, bool sat_ack_mask, bool reset_notification_mask, bool cmd_available_mask, bool busy_mask)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x05;
    configuration_w_serialize(&request, sat_ack, geolocation, ephemeris, deep_sleep, sat_ack_mask, reset_notification_mask, cmd_available_mask, busy_mask);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x85)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_w(bool sat_ack, bool geolocation, bool ephemeris, bool deep_sleep, bool sat_ack_mask, bool reset_notification_mask, bool cmd_available_mask, bool busy_mask)
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x05;
    configuration_w_serialize(&request, sat_ack, geolocation, ephemeris, deep_sleep, sat_ack_mask, reset_notification_mask, cmd_available_mask, busy_mask);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_configuration_w(configuration_w_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x85)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command configuration_r
//////////////////////////////////////////
static void configuration_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void configuration_r_deserialize(configuration_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    memcpy(&p_deserialized_data->data.id, &p_serialized_data->p_payload[0], 1);
    memcpy(&p_deserialized_data->data.hw_rev, &p_serialized_data->p_payload[1], 1);
    memcpy(&p_deserialized_data->data.fw_major_v, &p_serialized_data->p_payload[2], 1);
    memcpy(&p_deserialized_data->data.fw_minor_v, &p_serialized_data->p_payload[3], 1);
    memcpy(&p_deserialized_data->data.fw_rev_v, &p_serialized_data->p_payload[4], 1);
    p_deserialized_data->data.sat_ack = (p_serialized_data->p_payload[5] >> 0) & 0x01;
    p_deserialized_data->data.geolocation = (p_serialized_data->p_payload[5] >> 1) & 0x01;
    p_deserialized_data->data.ephemeris = (p_serialized_data->p_payload[5] >> 2) & 0x01;
    p_deserialized_data->data.deep_sleep = (p_serialized_data->p_payload[5] >> 3) & 0x01;
    //padding:12 bits. 2
    p_deserialized_data->data.sat_ack_mask = (p_serialized_data->p_payload[7] >> 0) & 0x01;
    p_deserialized_data->data.reset_notification_mask = (p_serialized_data->p_payload[7] >> 1) & 0x01;
    p_deserialized_data->data.cmd_available_mask = (p_serialized_data->p_payload[7] >> 2) & 0x01;
    p_deserialized_data->data.busy_mask = (p_serialized_data->p_payload[7] >> 3) & 0x01;
    //padding:4 bits. 1
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_r(configuration_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x15;
    configuration_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x95)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x15;
    configuration_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_configuration_r(configuration_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x95)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command configuration_save
//////////////////////////////////////////
static void configuration_save_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void configuration_save_deserialize(configuration_save_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_save(configuration_save_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x10;
    configuration_save_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x90)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_save_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_save()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x10;
    configuration_save_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_configuration_save(configuration_save_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x90)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_save_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command configuration_reset
//////////////////////////////////////////
static void configuration_reset_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void configuration_reset_deserialize(configuration_reset_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_configuration_reset(configuration_reset_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x11;
    configuration_reset_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x91)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_reset_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_configuration_reset()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x11;
    configuration_reset_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_configuration_reset(configuration_reset_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x91)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    configuration_reset_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command payload_w
//////////////////////////////////////////
static void payload_w_serialize(astronode_app_msg_t *p_serialized_data, uint16_t counter, const char *p_payload, uint16_t payload_length)
{
    p_serialized_data->p_payload[0] = (uint8_t)counter;
    p_serialized_data->p_payload[1] = (uint8_t) (counter >> 8);
    memcpy(&p_serialized_data->p_payload[2], p_payload, payload_length);
    p_serialized_data->payload_len += payload_length;
    p_serialized_data->payload_len += 2;
}

static void payload_w_deserialize(payload_w_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    memcpy(&p_deserialized_data->data.counter, &p_serialized_data->p_payload[0], 2);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_payload_w(payload_w_response_t *p_answer, uint16_t counter, const char *p_payload, uint16_t payload_length)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x25;
    payload_w_serialize(&request, counter, p_payload, payload_length);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xA5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    payload_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_payload_w(uint16_t counter, const char *p_payload, uint16_t payload_length)
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x25;
    payload_w_serialize(&request, counter, p_payload, payload_length);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_payload_w(payload_w_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xA5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    payload_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command payload_dequeue
//////////////////////////////////////////
static void payload_dequeue_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void payload_dequeue_deserialize(payload_dequeue_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    memcpy(&p_deserialized_data->data.counter, &p_serialized_data->p_payload[0], 2);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_payload_dequeue(payload_dequeue_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x26;
    payload_dequeue_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xA6)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    payload_dequeue_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_payload_dequeue()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x26;
    payload_dequeue_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_payload_dequeue(payload_dequeue_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xA6)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    payload_dequeue_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command payload_clear
//////////////////////////////////////////
static void payload_clear_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void payload_clear_deserialize(payload_clear_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_payload_clear(payload_clear_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x27;
    payload_clear_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xA7)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    payload_clear_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_payload_clear()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x27;
    payload_clear_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_payload_clear(payload_clear_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xA7)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    payload_clear_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command geolocation_w
//////////////////////////////////////////
static void geolocation_w_serialize(astronode_app_msg_t *p_serialized_data, int32_t lat, int32_t lng)
{
    p_serialized_data->p_payload[0] = (uint8_t)lat;
    p_serialized_data->p_payload[1] = (uint8_t) (lat >> 8);
    p_serialized_data->p_payload[2] = (uint8_t) (lat >> 16);
    p_serialized_data->p_payload[3] = (uint8_t) (lat >> 24);
    p_serialized_data->p_payload[4] = (uint8_t)lng;
    p_serialized_data->p_payload[5] = (uint8_t) (lng >> 8);
    p_serialized_data->p_payload[6] = (uint8_t) (lng >> 16);
    p_serialized_data->p_payload[7] = (uint8_t) (lng >> 24);
    p_serialized_data->payload_len += 8;
}

static void geolocation_w_deserialize(geolocation_w_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_geolocation_w(geolocation_w_response_t *p_answer, int32_t lat, int32_t lng)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x35;
    geolocation_w_serialize(&request, lat, lng);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xB5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    geolocation_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_geolocation_w(int32_t lat, int32_t lng)
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x35;
    geolocation_w_serialize(&request, lat, lng);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_geolocation_w(geolocation_w_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xB5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    geolocation_w_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command event_r
//////////////////////////////////////////
static void event_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void event_r_deserialize(event_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    p_deserialized_data->data.sak = (p_serialized_data->p_payload[0] >> 0) & 0x01;
    p_deserialized_data->data.reset = (p_serialized_data->p_payload[0] >> 1) & 0x01;
    p_deserialized_data->data.cmd = (p_serialized_data->p_payload[0] >> 2) & 0x01;
    p_deserialized_data->data.busy = (p_serialized_data->p_payload[0] >> 3) & 0x01;
    //padding:4 bits. 1
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_event_r(event_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x65;
    event_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    event_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_event_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x65;
    event_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_event_r(event_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    event_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command sak_r
//////////////////////////////////////////
static void sak_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void sak_r_deserialize(sak_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    memcpy(&p_deserialized_data->data.counter, &p_serialized_data->p_payload[0], 2);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_sak_r(sak_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x45;
    sak_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    sak_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_sak_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x45;
    sak_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_sak_r(sak_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    sak_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command sak_cl
//////////////////////////////////////////
static void sak_cl_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void sak_cl_deserialize(sak_cl_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_sak_cl(sak_cl_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x46;
    sak_cl_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC6)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    sak_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_sak_cl()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x46;
    sak_cl_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_sak_cl(sak_cl_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC6)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    sak_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command reset_cl
//////////////////////////////////////////
static void reset_cl_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void reset_cl_deserialize(reset_cl_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_reset_cl(reset_cl_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x55;
    reset_cl_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xD5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    reset_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_reset_cl()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x55;
    reset_cl_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_reset_cl(reset_cl_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xD5)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    reset_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command cmd_r
//////////////////////////////////////////
static void cmd_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void cmd_r_deserialize(cmd_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    memcpy(&p_deserialized_data->data.created_date, &p_serialized_data->p_payload[0], 4);
    p_deserialized_data->data.cmd_len = p_serialized_data->payload_len - 4;
    memcpy(p_deserialized_data->data.cmd, &p_serialized_data->p_payload[4], p_serialized_data->payload_len - 4);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_cmd_r(cmd_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x47;
    cmd_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC7)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    cmd_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_cmd_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x47;
    cmd_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_cmd_r(cmd_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC7)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    cmd_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command cmd_cl
//////////////////////////////////////////
static void cmd_cl_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void cmd_cl_deserialize(cmd_cl_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_cmd_cl(cmd_cl_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x48;
    cmd_cl_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC8)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    cmd_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_cmd_cl()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x48;
    cmd_cl_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_cmd_cl(cmd_cl_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xC8)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    cmd_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command rtc_r
//////////////////////////////////////////
static void rtc_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void rtc_r_deserialize(rtc_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    memcpy(&p_deserialized_data->data.time, &p_serialized_data->p_payload[0], 4);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_rtc_r(rtc_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x17;
    rtc_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x97)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    rtc_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_rtc_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x17;
    rtc_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_rtc_r(rtc_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x97)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    rtc_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command guid_r
//////////////////////////////////////////
static void guid_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void guid_r_deserialize(guid_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    p_deserialized_data->data.guid_len = p_serialized_data->payload_len - 0;
    memcpy(p_deserialized_data->data.guid, &p_serialized_data->p_payload[0], p_serialized_data->payload_len - 0);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_guid_r(guid_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x19;
    guid_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x99)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    guid_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_guid_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x19;
    guid_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_guid_r(guid_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x99)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    guid_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command sn_r
//////////////////////////////////////////
static void sn_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void sn_r_deserialize(sn_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    p_deserialized_data->data.sn_len = p_serialized_data->payload_len - 0;
    memcpy(p_deserialized_data->data.sn, &p_serialized_data->p_payload[0], p_serialized_data->payload_len - 0);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_sn_r(sn_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x1A;
    sn_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x9A)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    sn_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_sn_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x1A;
    sn_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_sn_r(sn_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x9A)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    sn_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command pn_r
//////////////////////////////////////////
static void pn_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void pn_r_deserialize(pn_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    p_deserialized_data->data.pn_len = p_serialized_data->payload_len - 0;
    memcpy(p_deserialized_data->data.pn, &p_serialized_data->p_payload[0], p_serialized_data->payload_len - 0);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_pn_r(pn_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x1B;
    pn_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x9B)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    pn_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_pn_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x1B;
    pn_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_pn_r(pn_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x9B)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    pn_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command eph_r
//////////////////////////////////////////
static void eph_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void eph_r_deserialize(eph_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    memcpy(&p_deserialized_data->data.next_pass, &p_serialized_data->p_payload[0], 4);
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_eph_r(eph_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x18;
    eph_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x98)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    eph_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_eph_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x18;
    eph_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_eph_r(eph_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x98)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    eph_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command context_save
//////////////////////////////////////////
static void context_save_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void context_save_deserialize(context_save_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_context_save(context_save_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x66;
    context_save_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE6)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    context_save_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_context_save()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x66;
    context_save_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_context_save(context_save_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE6)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    context_save_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command perf_counters_r
//////////////////////////////////////////
static void perf_counters_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void perf_counters_r_deserialize(perf_counters_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    // tlv 
    uint8_t tlv_byte_index = 0;
    while (tlv_byte_index < p_serialized_data->payload_len)
    {
        uint8_t tlv_item_type = p_serialized_data->p_payload[tlv_byte_index];
        uint8_t tlv_item_len = p_serialized_data->p_payload[tlv_byte_index + 1];
        switch (tlv_item_type)
        {
            case 0x01:
                memcpy(&p_deserialized_data->data.sat_search_phase, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x02:
                memcpy(&p_deserialized_data->data.sat_search_try, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x03:
                memcpy(&p_deserialized_data->data.sat_demod_phase, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x04:
                memcpy(&p_deserialized_data->data.sat_demod_try, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x05:
                memcpy(&p_deserialized_data->data.valid_sat_demod, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x06:
                memcpy(&p_deserialized_data->data.ack_demod_try, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x07:
                memcpy(&p_deserialized_data->data.valid_ack_demod, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x08:
                memcpy(&p_deserialized_data->data.msg_queued, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x09:
                memcpy(&p_deserialized_data->data.msg_dequeued, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x0A:
                memcpy(&p_deserialized_data->data.msg_ack, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x0B:
                memcpy(&p_deserialized_data->data.fragment_tx, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x0C:
                memcpy(&p_deserialized_data->data.fragment_ack, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x0D:
                memcpy(&p_deserialized_data->data.unicast_demod_try, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x0E:
                memcpy(&p_deserialized_data->data.valid_unicast_demod, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
        }
        tlv_byte_index += tlv_item_len + 2;
    }
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_perf_counters_r(perf_counters_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x67;
    perf_counters_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE7)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    perf_counters_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_perf_counters_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x67;
    perf_counters_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_perf_counters_r(perf_counters_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE7)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    perf_counters_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command perf_counters_cl
//////////////////////////////////////////
static void perf_counters_cl_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void perf_counters_cl_deserialize(perf_counters_cl_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_perf_counters_cl(perf_counters_cl_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x68;
    perf_counters_cl_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE8)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    perf_counters_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_perf_counters_cl()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x68;
    perf_counters_cl_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_perf_counters_cl(perf_counters_cl_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE8)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    perf_counters_cl_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command module_state_r
//////////////////////////////////////////
static void module_state_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void module_state_r_deserialize(module_state_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    // tlv 
    uint8_t tlv_byte_index = 0;
    while (tlv_byte_index < p_serialized_data->payload_len)
    {
        uint8_t tlv_item_type = p_serialized_data->p_payload[tlv_byte_index];
        uint8_t tlv_item_len = p_serialized_data->p_payload[tlv_byte_index + 1];
        switch (tlv_item_type)
        {
            case 0x41:
                memcpy(&p_deserialized_data->data.msg_queued, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x42:
                memcpy(&p_deserialized_data->data.ack_msg_queued, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x43:
                memcpy(&p_deserialized_data->data.last_reset_reason, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x44:
                memcpy(&p_deserialized_data->data.uptime, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
        }
        tlv_byte_index += tlv_item_len + 2;
    }
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_module_state_r(module_state_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x69;
    module_state_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE9)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    module_state_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_module_state_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x69;
    module_state_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_module_state_r(module_state_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xE9)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    module_state_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command last_contact_r
//////////////////////////////////////////
static void last_contact_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void last_contact_r_deserialize(last_contact_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    // tlv 
    uint8_t tlv_byte_index = 0;
    while (tlv_byte_index < p_serialized_data->payload_len)
    {
        uint8_t tlv_item_type = p_serialized_data->p_payload[tlv_byte_index];
        uint8_t tlv_item_len = p_serialized_data->p_payload[tlv_byte_index + 1];
        switch (tlv_item_type)
        {
            case 0x51:
                memcpy(&p_deserialized_data->data.start_time, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x52:
                memcpy(&p_deserialized_data->data.end_time, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x53:
                memcpy(&p_deserialized_data->data.peak_rssi, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x54:
                memcpy(&p_deserialized_data->data.peak_time, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
        }
        tlv_byte_index += tlv_item_len + 2;
    }
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_last_contact_r(last_contact_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x6A;
    last_contact_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xEA)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    last_contact_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_last_contact_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x6A;
    last_contact_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_last_contact_r(last_contact_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xEA)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    last_contact_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command environment_r
//////////////////////////////////////////
static void environment_r_serialize(astronode_app_msg_t *p_serialized_data)
{
    p_serialized_data->payload_len += 0;
}

static void environment_r_deserialize(environment_r_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
    // tlv 
    uint8_t tlv_byte_index = 0;
    while (tlv_byte_index < p_serialized_data->payload_len)
    {
        uint8_t tlv_item_type = p_serialized_data->p_payload[tlv_byte_index];
        uint8_t tlv_item_len = p_serialized_data->p_payload[tlv_byte_index + 1];
        switch (tlv_item_type)
        {
            case 0x61:
                memcpy(&p_deserialized_data->data.last_mac_result, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x62:
                memcpy(&p_deserialized_data->data.last_rssi, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
            case 0x63:
                memcpy(&p_deserialized_data->data.time_since_satdet, &p_serialized_data->p_payload[tlv_byte_index + 2], tlv_item_len);
                break;
        }
        tlv_byte_index += tlv_item_len + 2;
    }
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_environment_r(environment_r_response_t *p_answer)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x6B;
    environment_r_serialize(&request);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xEB)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    environment_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_environment_r()
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x6B;
    environment_r_serialize(&request);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_environment_r(environment_r_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0xEB)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    environment_r_deserialize(p_answer, &answer);
    return ans_status;
}
#endif

//////////////////////////////////////////
// Command config_sat_search
//////////////////////////////////////////
static void config_sat_search_serialize(astronode_app_msg_t *p_serialized_data, uint8_t setting, bool search_wo_msg)
{
    p_serialized_data->p_payload[0] = (uint8_t)setting;
    p_serialized_data->p_payload[1] = search_wo_msg;
    //padding:7 bits
    p_serialized_data->payload_len += 2;
}

static void config_sat_search_deserialize(config_sat_search_response_t *p_deserialized_data, const astronode_app_msg_t *p_serialized_data)
{
    p_deserialized_data->data.opcode = p_serialized_data->op_code;
}

#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
as_return_status_t astronode_request_config_sat_search(config_sat_search_response_t *p_answer, uint8_t setting, bool search_wo_msg)
{
    astronode_app_msg_t request = {0};
    astronode_app_msg_t answer = {0};

    request.op_code = 0x07;
    config_sat_search_serialize(&request, setting, search_wo_msg);

    as_return_status_t ans_status = astronode_transport_send_receive(&request, &answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x87)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    config_sat_search_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
as_return_status_t astronode_send_async_config_sat_search(uint8_t setting, bool search_wo_msg)
{
    astronode_app_msg_t request = {0};

    request.op_code = 0x07;
    config_sat_search_serialize(&request, setting, search_wo_msg);

    return astronode_transport_send(&request);
}

as_return_status_t astronode_poll_answer_config_sat_search(config_sat_search_response_t *p_answer)
{
    astronode_app_msg_t answer = {0};

    as_return_status_t ans_status = astronode_transport_receive(&answer);
    if (ans_status != RS_ASSET_SUCCESS) 
    {
        return ans_status;
    }
    if (answer.op_code != 0x87)
    {
        p_answer->error = (uint16_t) (answer.p_payload[0] & 0xFF) | (uint16_t) (answer.p_payload[1] << 8);
        return RS_ASTRONODE_FAILURE;
    }
    config_sat_search_deserialize(p_answer, &answer);
    return ans_status;
}
#endif
