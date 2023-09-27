#include "device_interface.h"

void di_device_initialize(void){

}

// Astronode UART
return_status_t di_uart_astronode_write(const uint8_t *p_data, uint16_t length){
    return RS_SUCCESS;
}

return_status_t di_uart_astronode_receive_char(uint8_t *p_rx_char)
{
    return RS_SUCCESS;
}

uint32_t di_clock_get_system_tick(void){
    return 0;
}

bool di_clock_is_systick_timeout_over(uint32_t starting_value, uint32_t duration){
    return (di_clock_get_system_tick() - starting_value > duration) ? true : false;
}

void di_gpio_astronode_write_wake_up_pin(bool state)
{

}

void di_gpio_astronode_write_reset_pin(bool state)
{

}

bool di_gpio_astronode_read_event_pin(void)
{
    return false;
}

void di_gpio_register_event_pin_it_callback(void (*function_pointer)(void))
{

}

void di_sleep_ms(uint32_t duration_ms)
{

}