#include <stdint.h>
#include <stdbool.h>

typedef enum return_status_t
{
    RS_SUCCESS = 0U,
    RS_FAILURE
} return_status_t;

/**
 * @brief Initialize hardware
 */
void di_device_initialize(void);

/**
 * @brief Send an amount of data in blocking mode to astronode uart.
 * @param p_tx_buffer Pointer to data buffer.
 * @param len Amount of data elements to be sent.
 * @return RS_SUCCESS on success.
 */
return_status_t di_uart_astronode_write(const uint8_t *p_tx_buffer, uint16_t len);

/**
 * @brief Receive a character from Astronode uart in blocking mode.
 * @param p_rx_char Pointer to the received character.
 * @return RS_SUCCESS if a character is received and copied to p_rx_char, RS_FAILURE otherwise.
 */
return_status_t di_uart_astronode_receive_char(uint8_t *p_rx_char);

/**
 * @brief Set the astronode wake-up pin value.
 * @param state True to set the pin high, false to set it low.
 */
void di_gpio_astronode_write_wake_up_pin(bool state);

/**
 * @brief Set the astronode reset pin value.
 * @param state True to set the pin high, false to set it low.
 */
void di_gpio_astronode_write_reset_pin(bool state);

/**
 * @brief Return the astronode event pin value.
 * @return True if the pin is high, false if it is low.
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
