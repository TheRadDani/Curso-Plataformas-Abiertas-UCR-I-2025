set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_C_FLAGS_INIT "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -std=gnu++14")

set(CMAKE_EXE_LINKER_FLAGS_INIT
    "-Wl,-Map=firmware.map \
    -T${CMAKE_SOURCE_DIR}/linker_script.ld \
    -nostdlib"
)