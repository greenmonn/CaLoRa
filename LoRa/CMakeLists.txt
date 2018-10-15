# project settings
cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME LoRa)
project(${PROJECT_NAME})

#===========================================#
#  generate RadioHead Lib                   #
#===========================================#
set(RH_PATH ${CMAKE_SOURCE_DIR}/RadioHead)
include_directories(${RH_PATH})
file(GLOB RH_SRCS ${RH_PATH}/*.cpp)
file(GLOB RH_HDRS ${RH_PATH}/*.h)
generate_arduino_library(RadioHead SRCS ${RH_SRCS} HDRS ${RH_HDRS})

#===========================================#
#  generate LoRaWan Lib                     #
#===========================================#
set(LORA_PATH ${CMAKE_SOURCE_DIR}/LoRaWan)
include_directories(${LORA_PATH})
file(GLOB LORA_SRCS ${LORA_PATH}/*.cpp)
file(GLOB LORA_HDRS ${LORA_PATH}/*.h)
#set(${CMAKE_PROJECT_NAME}_SRCS "${LORA_SRCS}")
#set(${CMAKE_PROJECT_NAME}_HDRS "${LORA_HDRS}")
generate_arduino_library(LoRaWan SRCS ${LORA_SRCS} HDRS ${LORA_HDRS})

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
generate_arduino_firmware(${CMAKE_PROJECT_NAME} LIBS RadioHead LoRaWan)
