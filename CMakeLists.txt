cmake_minimum_required(VERSION 3.10)

project(hab)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(rs232 SHARED src/devices/serial/rs232.c)
add_library(serial SHARED src/devices/serial/serial.cpp)
add_library(geiger SHARED src/devices/serial/geiger_counter.cpp)
add_library(i2c SHARED src/devices/i2c/i2c_device.cpp)
add_library(imu SHARED src/devices/i2c/imu.cpp)

add_executable(hab src/hab.cpp)
target_link_libraries(serial rs232)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(i2c ${WIRINGPI_LIBRARIES})
target_link_libraries(i2c imu)
target_link_libraries(hab rs232 serial geiger i2c imu)

add_custom_command(
	TARGET hab POST_BUILD
	COMMAND -E copy
	${CMAKE_SOURCE_DIR}/src/devices/devices_config.json
	${CMAKE_CURRENT_BINARY_DIR}/devices_config.json)
