# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/opt/pico-sdk")#only true for my machine

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PicoRGB C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(main main.c PicoRGB.c adc_driver.c)

pico_generate_pio_header(main ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

pico_set_program_name(main "picoRGB")
pico_set_program_version(main "1.0")

pico_enable_stdio_uart(main 0)
pico_enable_stdio_usb(main 1)

# Add the standard library to the build
target_link_libraries(main pico_stdlib)
target_link_libraries(main pico_stdlib hardware_pio hardware_sync hardware_adc hardware_pio hardware_clocks)

pico_add_extra_outputs(main)

