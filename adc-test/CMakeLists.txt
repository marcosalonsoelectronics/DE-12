cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(adc-test)

# Initialize the SDK
pico_sdk_init()

add_executable(adc-test adc-test.c )

# pull in common dependencies
target_link_libraries(adc-test pico_stdlib hardware_adc hardware_gpio)

# create map/bin/hex file etc.
pico_add_extra_outputs(adc-test)


