add_library(astronode_lib STATIC
        astronode_application.c
        astronode_transport.c
        astronode_gpio.c
        )

target_include_directories(astronode_lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_compile_options(astronode_lib PRIVATE
        -Wall -Wextra -Wpedantic
        )

