cmake_minimum_required(VERSION 3.10)
project(C_JSON_EXAMPLE CXX)  # Change C to CXX for C++ support

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.5
)
FetchContent_MakeAvailable(json)

add_executable(myprogram src/main.cpp)  # Rename your file to .cpp

target_link_libraries(myprogram PRIVATE nlohmann_json::nlohmann_json)
