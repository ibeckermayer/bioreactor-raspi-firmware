cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

# Find the wiringPi library on device
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)


add_subdirectory(src)
add_subdirectory(test)
