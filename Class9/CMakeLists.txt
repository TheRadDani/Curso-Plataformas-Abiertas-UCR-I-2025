# CMake configuration for compiling Embedded C program
cmake_minimum_required(VERSION 3.10)
project(Peripheral_Communication)

# Set compiler options (modify for embedded targets)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -O2")  # Enable optimizations

# Add source file
add_executable(peripheral_comm example14.c)
