#include <stdio.h>
#include <device_interface.h>
#include <astronode_application.h>
#include <astronode_gpio.h>

int main() {
    di_device_initialize();

    astronode_gpio_reset_device();

    // Send the command and wait for an answer
    configuration_r_response_t ans = {0};
    as_return_status_t ret = astronode_request_configuration_r(&ans);
    if (ret != RS_ASSET_SUCCESS)
    {
        printf("Error\n");
        // Error
    }

    printf("fw_major_v:%d fw_minor_v:%d\n", ans.data.fw_major_v, ans.data.fw_minor_v);
    return 0;
}
