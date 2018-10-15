# project settings
cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME LoRa)
project(${PROJECT_NAME})

#===========================================#
#  generate LoRaWan Lib                     #
#===========================================#
set(LORAWAN_PATH ${CMAKE_SOURCE_DIR}/LoRaWan)
set(RH_PATH ${LORAWAN_PATH}/RadioHead)
include_directories(${LORAWAN_PATH})
include_directories(${RH_PATH})

file(GLOB LORAWAN_SRCS ${LORAWAN_PATH}/*.cpp)
file(GLOB LORAWAN_HDRS ${LORAWAN_PATH}/*.h)
file(GLOB RH_SRCS ${RH_PATH}/*.cpp)
file(GLOB RH_SRCS ${RH_PATH}/*.cpp)

generate_arduino_library(
        LoRaWan
        SRCS ${LORAWAN_SRCS} ${RH_SRCS}
        HDRS ${LORAWAN_HDRS} ${RH_HDRS})

#===========================================#
#  generate arduino firmware                #
#===========================================#
set(${CMAKE_PROJECT_NAME}_SKETCH LoRa.ino)
set(${CMAKE_PROJECT_NAME}_BOARD uno)

file(GLOB ARD_PORT /dev/cu.wchusbserial*)

if(WIN32)
    file(READ ${CMAKE_SOURCE_DIR}/WinSerialPort.txt ARD_PORT)
endif()

set(${CMAKE_PROJECT_NAME}_PORT ${ARD_PORT})
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
# set(mega.upload.speed 115200)
generate_arduino_firmware(${CMAKE_PROJECT_NAME} LIBS LoRaWan)
