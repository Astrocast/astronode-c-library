#ifndef SAMPLE_PROJECT_ASTRONODE_GPIO_H
#define SAMPLE_PROJECT_ASTRONODE_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <stdbool.h>


//------------------------------------------------------------------------------
// Function declarations
//------------------------------------------------------------------------------
/**
 * @brief Set the astronode wake-up pin value.
 * @param state
 */
void astronode_gpio_write_wake_up_pin(bool state);

/**
 * @brief Set the astronode reset pin value. Astronode reset is active on rising edge.
 * To reset the Astronode, the pin must be high for 1ms.
 * @param state
 */
void astronode_gpio_write_reset_pin(bool state);

/**
 * @brief Returns the astronode event pin value.
 * @return True if signal is high.
 */
bool astronode_gpio_read_event_pin(void);

/**
 * @brief Perform a reset cycle to the Astronode. Active wait of 1ms low then 1ms high.
 */
void astronode_gpio_reset_device(void);

#ifdef __cplusplus
}
#endif

#endif //SAMPLE_PROJECT_ASTRONODE_GPIO_H