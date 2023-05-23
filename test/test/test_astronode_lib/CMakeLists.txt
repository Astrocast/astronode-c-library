# astronode application
add_executable(test_astronode_application
    test_astronode_application.c
)

add_test(test_astronode_application_test test_astronode_application)

target_link_libraries(test_astronode_application
        astronode_lib
        Unity
        )

# astronode transport
add_executable(test_astronode_transport
        test_astronode_transport.c
        )

add_test(test_astronode_transport_test test_astronode_transport)

target_link_libraries(test_astronode_transport
        astronode_lib
        Unity
        )