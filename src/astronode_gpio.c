//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "astronode_gpio.h"
#include "device_interface.h"


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------
void astronode_gpio_write_wake_up_pin(bool state)
{
    di_gpio_astronode_write_wake_up_pin(state);
}

void astronode_gpio_write_reset_pin(bool state)
{
    di_gpio_astronode_write_reset_pin(state);
}

bool astronode_gpio_read_event_pin(void)
{
    return di_gpio_astronode_read_event_pin();
}

void astronode_gpio_reset_device(void)
{
    astronode_gpio_write_reset_pin(false);
    di_sleep_ms(1);
    astronode_gpio_write_reset_pin(true);
    di_sleep_ms(1);
    astronode_gpio_write_reset_pin(false);
}