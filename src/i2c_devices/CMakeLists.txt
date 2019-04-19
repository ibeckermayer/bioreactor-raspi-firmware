cmake_minimum_required(VERSION 3.5)
project(i2c_devices)

set(SOURCE_FILES I2CSlave.cpp I2CSlave.h I2CSlaveError.cpp I2CSlaveError.h MCP9600.cpp MCP9600.h)

# compile i2c_devices as a dynamic library
add_library(i2c_devices SHARED ${SOURCE_FILES})

# set it such that any target that links to this target can find the header files here
target_include_directories(i2c_devices PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# link to wiringPi libraries
target_link_libraries(i2c_devices ${WIRINGPI_LIBRARIES})