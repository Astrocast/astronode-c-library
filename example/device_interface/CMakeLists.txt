add_library(device_interface STATIC
        device_interface.c
        )

target_include_directories(astronode_lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

