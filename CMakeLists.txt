cmake_minimum_required(VERSION 3.5)
project(firmware)

set(CMAKE_CXX_STANDARD 11)

add_executable(firmware I2CSlave.cpp I2CSlave.h I2CSlaveError.cpp I2CSlaveError.h MCP9600.cpp MCP9600.h main.cpp)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(firmware ${WIRINGPI_LIBRARIES})
