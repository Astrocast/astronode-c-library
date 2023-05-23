#include "stdint.h"
#include "stdbool.h"

typedef enum return_status_t
{
    RS_SUCCESS = 0U,
    RS_FAILURE
} return_status_t;

/**
 * @brief Send an amount of data in blocking mode to astronode uart.
 * @param p_tx_buffer Pointer to data buffer.
 * @param len Amount of data elements to be sent.
 * @return RS_SUCCESS on success.
 */
return_status_t di_uart_astronode_write(const uint8_t *p_tx_buffer, uint16_t len);

/**
 * @brief Register the function that is called when a character is received (in interrupt mode).
 * @param function_pointer Pointer to the callback function. Char argument is the received char.
 */
void di_uart_astronode_register_rx_it_callback(void (*function_pointer)(uint8_t));

/**
 * @brief
 * @param p_rx_char
 * @return
 */
return_status_t di_uart_astronode_receive_char(uint8_t *p_rx_char);

/**
 * @brief Set the astronode wake-up pin value.
 * @param state
 */
void di_gpio_astronode_write_wake_up_pin(bool state);

/**
 * @brief Set the astronode reset pin value. Astronode reset is active on rising edge.
 * To reset the Astronode, the pin must be high for 1ms.
 * @param state
 */
void di_gpio_astronode_write_reset_pin(bool state);

/**
 * @brief Returns the astronode event pin value.
 * @return True if signal is high.
 */
bool di_gpio_astronode_read_event_pin(void);


/**
 * @brief Set the astronode wake-up pin value.
 * @param state
 */
void di_gpio_astronode_write_wake_up_pin(bool state);

/**
 * @brief Set the astronode reset pin value.
 * @param state
 */
void di_gpio_astronode_write_reset_pin(bool state);

/**
 * @brief Returns the astronode event pin value.
 * @return True if signal is high.
 */
bool di_gpio_astronode_read_event_pin(void);

/**
 * @brief Get the actual systick.
 * @return Systick in ms.
 */
uint32_t di_clock_get_system_tick(void);

/**
 * @brief Measure the elapsed time from starting value to now and compute if timeout is elapsed.
 * @param starting_value The starting time in ms.
 * @param duration The timeout in ms.
 * @return True is timeout is reached. False otherwise.
 */
bool di_clock_is_systick_timeout_over(uint32_t starting_value, uint32_t duration);

/**
 * @brief Active wait function.
 * @param duration_ms
 */
void di_sleep_ms(uint32_t duration_ms);
