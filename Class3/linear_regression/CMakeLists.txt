cmake_minimum_required(VERSION 3.10)

# Project name
project(LinearRegression C)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable
add_executable(linear_regression main.c)

# Link the math library
target_link_libraries(linear_regression m)
