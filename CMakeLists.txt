cmake_minimum_required(VERSION 3.13)

# Initialize pico-sdk from Git.
set(PICO_SDK_FETCH_FROM_GIT on)

# Include the cmake pico script.
list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_CURRENT_LIST_DIR}/cmake"
)
include (pico_sdk_import)

# Initialize the project.
project(PicoRGB)

# Initialize the Pico SDK.
pico_sdk_init(PicoRGB)

set(CMAKE_C_STANDARD 17)

# Set directories.
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

# Specify the source files.
add_executable(main
        ${SRC_DIR}/main.c
        ${SRC_DIR}/PicoRGB.c
        ${SRC_DIR}/adc_driver.c
)

# Set the compiler options.
target_compile_options(main
        PRIVATE -W -Wall -Wextra -Werror
)

# Set the include directory.
target_include_directories(main
        PRIVATE ${INC_DIR}
)

# Link Pico SDK libraries.
target_link_libraries(main pico_stdlib hardware_pio hardware_sync hardware_adc hardware_pio hardware_clocks)

# Compile the PIO program and generate the ws2812.pio.h file.
pico_generate_pio_header(main ${SRC_DIR}/ws2812.pio)

# Start USB and disable UART.
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# Create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)
