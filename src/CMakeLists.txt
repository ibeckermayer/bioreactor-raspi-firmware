cmake_minimum_required(VERSION 3.5)
project(firmware_main)

add_subdirectory(i2c_devices)
set(SOURCE_FILES main.cpp)

add_executable(firmware_main ${SOURCE_FILES})
target_link_libraries(firmware_main i2c_devices)

