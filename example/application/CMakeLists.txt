project(application_example)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} astronode_lib device_interface)

