project(astronode_lib)

add_library(${PROJECT_NAME} STATIC
        astronode_application.c
        astronode_transport.c
        astronode_gpio.c
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

# TODO remove this part
target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wpedantic
        )

