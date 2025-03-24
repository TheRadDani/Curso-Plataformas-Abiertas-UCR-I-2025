cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Add the executable
add_executable(myprogram main.c)

# Add compile definitions for Debug and Release
target_compile_definitions(myprogram PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# Set different compile options for Debug and Release
target_compile_options(myprogram PRIVATE
    $<$<CONFIG:Debug>:-Wall -g>
    $<$<CONFIG:Release>:-O2>
)
