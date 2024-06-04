cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pwm-test)

# Initialize the SDK
pico_sdk_init()

add_executable(pwm-test
        pwm-test.c
        )

# pull in common dependencies
target_link_libraries(pwm-test pico_stdlib hardware_pwm)


# create map/bin/hex file etc.
pico_add_extra_outputs(pwm-test)

