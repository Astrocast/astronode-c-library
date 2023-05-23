# Astronode C library 
## Brief
This library is a C implementation of the [Astronode serial commands protocol](https://docs.astrocast.com/docs/products/astronode-api/introduction). 

- [Astronode C library](#astronode-c-library)
    * [Brief](#brief)
    * [Description](#description)
        + [Folder structure](#folder-structure)
        + [Syncronous or asynchronous serial communication](#syncronous-or-asynchronous-serial-communication)
        + [Device interface](#device-interface)
    * [How to use it](#how-to-use-it)
        + [How to get the answer](#how-to-get-the-answer)
        + [Use synchronous mode example](#use-synchronous-mode-example)
        + [Use asynchronous mode example](#use-asynchronous-mode-example)
    * [GPIO](#gpio)
    * [Compiler and build options](#compiler-and-build-options)

<small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small>


## Description
The astronode library allows the asset application to communicate with the astronode. 
It contains all Astronode [commands](https://docs.astrocast.com/docs/products/astronode-api/commands-definition) and performs the serialization/deserialization, encoding/decoding, crc check. <br>
The device interface allows the library to be platform independent. 

```text
asset───────────────────────────────────────────┐
│                                               │
│               ┌─────────────────┐             │
│               │asset_application│             │
│               └─────┐▲──────┐▲──┘             │
│                     ││      ││                │
│ astronode_lib───────┼┼──────┼┼──────────────┐ │
│ │                   ││      ││              │ │
│ │  ┌────────────────▼└───┐  ││              │ │
│ │  │astronode_application│  ││              │ │
│ │  └──────────────┐▲─────┘  ││              │ │
│ │                 ││        ││              │ │
│ │                 ││        ││              │ │
│ │   ┌─────────────▼└────┐ ┌─▼└───────────┐  │ │
│ │   │astronode_transport│ │astronode_gpio│  │ │
│ │   └─────────────▲┌────┘ └─▲┌───────────┘  │ │
│ │                 ││        ││              │ │
│ └─────────────────┼┼────────┼┼──────────────┘ │
│                   ││        ││                │
│                ┌──┘▼────────┘▼──┐             │
│                │device_interface│             │
│                └───────┐▲───────┘             │
│                        ││                     │
│               ┌────────▼└───────┐             │
│               │     hardware    │             │
│               └────────┐▲───────┘             │
│                        ││                     │
└────────────────────────┼┼─────────────────────┘
                         ││
                   ┌─────▼└───────┐
                   │  astronode   │
                   └──────────────┘
```


### Folder structure
| Files                 | Content                                                                                                                                                          |
|-----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| astronode_application | Serialize and deserialize astronode commands. [online doc.](https://docs.astrocast.com/docs/products/astronode-api/protocol-layer/application-layer-description) |
| astronode_transport   | Encode and decode serialized commands. [online doc.](https://docs.astrocast.com/docs/products/astronode-api/protocol-layer/transport-layer-description)          |
| astronode_gpio        | Access and control the device gpio.                                                                                                                              |
| astronode_definitions | Contains opcodes and structures.                                                                                                                                 |
&nbsp;

### Syncronous or asynchronous serial communication
The library is designed to handle synchronous (blocking) and asynchronous (by interrupt) serial communication. In synchronous mode, the asset is blocking (active wait) until the Astonode answers.

In asynchronous mode, the answer is stored by interrupt and the program should poll the function astronode_poll_answer_xxx to get the answer.

Enabling/disabling modes is done in astronode_definitions.h: <br>
`ASTRONODE_TRANSPORT_BLOCKING_MODE` <br>
`ASTRONODE_TRANSPORT_ASYNC_MODE` <br>

### Device interface
In order to interface with the hardware, the library will call generic functions located in device_interface file. 
All device interface function should be mapped to the corresponding HAL functions of the specific platform. 

Example, the wake-up pin for the board B-U5851-IOT02A from ST.
```c
void di_gpio_astronode_write_wake_up_pin(bool state)
{
     HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, state);
}
```

## How to use it
To communicate, the asset sends a command, then waits for the Astronode answer. <br>
Each command has one synchronous function (which send the command and wait for the answer):
> as_return_status_t astronode_request_**command_name**(**command_name**_response_t)

And two asynchronous functions (one which send the command, the other to poll the answer):
> as_return_status_t astronode_send_async_**command_name**() <br>
> as_return_status_t astronode_poll_answer_**command_name**(**command_name**_response_t)

The return value as_return_status_t indicates the status of the communication. <br>
```c
typedef enum as_return_status_t
{
RS_ASSET_SUCCESS = 0U,  /*!< Operation succeed */
RS_ASSET_CRC_ERROR,     /*!< CRC error on Astronode answer */
RS_ASSET_BUSY,          /*!< Waiting for Astronode answer */
RS_ASSET_TIMEOUT,       /*!< Astronode did not answer before timeout */
RS_ASSET_FAILURE,       /*!< Failure in communication with the Astronode */
RS_ASTRONODE_FAILURE,   /*!< Astronode answers an error (0xFF opcode) */
} as_return_status_t;
```

**Note:**
RS_ASSET_BUSY is not available in synchronous mode.

**Note:**
The communication with the Astronode is sequential, therefore, wait for the answer (or timeout / error) before sending a new command.

### How to get the answer
The answer is available in the argument **command_name**_response_t. 
> astronode_request_**command_name**(*command_name**_response_t)

or
> astronode_poll_answer_**command_name**(**command_name**_response_t)

Depending on the return status, the answer (**command_name**_response_t) may have a different type (using union) or be empty. 
- If return status equals RS_ASSET_FAILURE, RS_ASSET_CRC_ERROR, RS_ASSET_BUSY, RS_ASSET_TIMEOUT, the answer is empty.
- If return status equals RS_ASTRONODE_FAILURE, the answer is an enum astronode_error_code corresponding to the error code returned by the Astronode. [online doc.](https://docs.astrocast.com/docs/products/astronode-api/commands-definition#errors).
- If return status equals RS_ASSET_SUCCESS, the type is a structure depending on the command, **command_name**_response_data_t 

For example, if the return status of *astronode_request_configuration_r* is RS_ASSET_SUCCESS, *configuration_r_response_t* type will be the structure *configuration_r_response_data_t*.


### Use synchronous mode example
Example to read the configuration of the Astronode:
```c
#include "astronode_application.h"
#include "astronode_transport.h"
#include "device_interface.h"

int main(void)
{
    di_device_initialize();

    // Send the command and wait for an answer
    configuration_r_response_t ans = {0};
    as_return_status_t ret = astronode_request_configuration_r(&ans);   
    if (ret != RS_ASSET_SUCCESS)
    {
        // Error
    }
    // For example, firmware version is: ans.data.fw_major_v, ans.data.fw_minor_v, ans.data.fw_rev_v
}
```

### Use asynchronous mode example
First, configure your device to receive characters from the Astonode by interrupt. Then register the callback:
> di_uart_astronode_register_rx_it_callback(astronode_transport_it_receive_char_handler);

By this way, the function astronode_transport_it_receive_char_handler will be notified when a character is received.

Example to read the configuration of the Astronode:
```c
#include "astronode_application.h"
#include "astronode_transport.h"
#include "device_interface.h"

int main(void)
{
    di_device_initialize();
    di_uart_user_register_rx_it_callback(user_interface_rx_interrupt_handler);

    // Send the command
    as_return_status_t ret = astronode_send_async_configuration_r();   
    if (ret != RS_ASSET_SUCCESS)
    {
        // Error
    }
    
    // Wait for the answer
    configuration_r_response_t ans = {0};
    ret = RS_ASSET_BUSY;
    while (ret == RS_ASSET_BUSY)
    {
        ret = astronode_poll_answer_configuration_r(&ans);  // Non blocking operation
        // Free time to do other operations
    }
    if (ret == RS_SUCCESS)
    {
        // For example, firmware version is: ans.data.fw_major_v, ans.data.fw_minor_v, ans.data.fw_rev_v
    }
    else
    {
        // Error    
    }
}
```

## GPIO
The gpio event, reset and wake-up can be controlled by the functions located in astronode_gpio.c. 


## Compiler and build options

