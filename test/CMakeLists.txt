cmake_minimum_required(VERSION 3.5)
project(firmware_tests)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

set(SOURCE_FILES main.cpp MCP9600_test.cpp)

add_executable(firmware_tests ${SOURCE_FILES})

target_link_libraries(firmware_tests gtest gtest_main i2c_devices)
