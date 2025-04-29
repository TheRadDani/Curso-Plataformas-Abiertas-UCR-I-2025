cmake_minimum_required(VERSION 3.20)
project(arduino_tflite C CXX ASM)

# Toolchain setup
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain.cmake)

# TensorFlow Lite Micro configuration
set(TFLM_ROOT ${CMAKE_SOURCE_DIR}/tflite-micro)
include_directories(
    ${TFLM_ROOT}
    ${TFLM_ROOT}/tensorflow/lite/micro/arduino
    ${TFLM_ROOT}/tensorflow/lite/micro
)

# Source files
file(GLOB_RECURSE TFLM_SOURCES
    "${TFLM_ROOT}/tensorflow/lite/micro/*.cc"
    "${TFLM_ROOT}/tensorflow/lite/micro/arduino/*.cc"
    "${TFLM_ROOT}/tensorflow/lite/micro/kernels/*.cc"
)

# Remove problematic files
list(REMOVE_ITEM TFLM_SOURCES
    ${TFLM_ROOT}/tensorflow/lite/micro/micro_interpreter_test.cc
)

add_executable(firmware
    src/main.cpp
    ${TFLM_SOURCES}
)

# Nano 33 BLE specific flags
target_compile_options(firmware PRIVATE
    -DARDUINO=1
    -DARDUINO_ARDUINO_NANO33BLE
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -mthumb
    -Wall
    -Os
)

target_link_options(firmware PRIVATE
    -Wl,--gc-sections
    -Wl,--check-sections
    -Wl,--entry=Reset_Handler
    -Wl,--unresolved-symbols=report-all
    -Wl,--warn-common
    -Wl,--warn-section-align
)