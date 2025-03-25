cmake_minimum_required(VERSION 3.10)
project(MyProject)
set(CMAKE_C_STANDARD 11)
# Add executable
add_executable(main main.c utils.c)

# Set compiler flags
target_compile_options(main PRIVATE -Wall -g)

# Link libraries (e.g., pthread)
target_link_libraries(main PRIVATE pthread)