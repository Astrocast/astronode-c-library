add_library(application STATIC
        main.c
        )

target_include_directories(astronode_lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

