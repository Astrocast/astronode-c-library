#ifndef ASTRONODE_TRANSPORT_H
#define ASTRONODE_TRANSPORT_H

#ifdef __cplusplus
extern "C" {
#endif


//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
// Standard

// Astrocast
#include "astronode_definitions.h"


//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------
#ifdef ASTRONODE_TRANSPORT_BLOCKING_MODE
/**
 * @brief Send a command to the Astronode and wait for an answer.
 * @param p_request The message to send to the Astronode.
 * @param p_answer The answer from the Astonode.
 * @return RS_ASSET_SUCCESS on success. Otherwise RS_ASSET_CRC_ERROR, RS_ASSET_TIMEOUT, RS_ASSET_FAILURE, RS_ASTRONODE_FAILURE.
 */
as_return_status_t astronode_transport_send_receive(const astronode_app_msg_t *p_request, astronode_app_msg_t *p_answer);   // TODO: move answer to the first argument.
#endif /* ASTRONODE_TRANSPORT_BLOCKING_MODE */

#ifdef ASTRONODE_TRANSPORT_ASYNC_MODE
/**
 * @brief Send a command to the Astronode.
 * @param p_request The message to send to the Astronode.
 * @return RS_ASSET_SUCCESS on success. RS_ASTRONODE_FAILURE on uart issue (asset).
 */
as_return_status_t astronode_transport_send(const astronode_app_msg_t *p_request);

/**
 * @brief Check if a response form the Astronode is available.
 * @param p_answer The answer from the Astronode if it's available.
 * @return RS_ASSET_SUCCESS if the answer is available. RS_ASSET_BUSY when the device is waiting for the answer.
 *  Otherwise the error status are RS_ASSET_CRC_ERROR, RS_ASSET_TIMEOUT, RS_ASSET_FAILURE, RS_ASTRONODE_FAILURE.
 */
as_return_status_t astronode_transport_receive(astronode_app_msg_t *p_answer);

/**
 * @brief This callback is called when a character is received from the Astronode.
 * @param rx_char The received character. 
 */
void astronode_transport_it_receive_char_handler(uint8_t rx_char);

#endif  /* ASTRONODE_TRANSPORT_ASYNC_MODE */

#ifdef __cplusplus
}
#endif

#endif /* ASTRONODE_TRANSPORT_H */