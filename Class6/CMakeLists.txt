cmake_minimum_required(VERSION 3.10)

project(PROJECT C)

set(CMAMKE_C_STANDARD 11)
set(CMAKE_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")

add_executable(main main.c)

add_custom_target(generate_assembly ALL
    COMMAND ${CMAKE_C_COMPILER} -S -O2 -g ${CMAKE_SOURCE_DIR}/
    DEPENDS main.c
    COMMENT "Generating assembly code from C source file"
)