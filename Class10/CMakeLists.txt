cmake_minimum_required(VERSION 3.13)

# Import SDK (use full path if environment variable not set)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_onnx C CXX ASM)

set(PICO_BUILD_PICOTOOL OFF)

# Initialize SDK
pico_sdk_init()

# Add executable
add_executable(pico_onnx
    pico.c
)

# Link libraries
target_link_libraries(pico_onnx
    pico_stdlib
    hardware_gpio
)

# Enable USB output
pico_enable_stdio_usb(pico_onnx 1)
pico_add_extra_outputs(pico_onnx)