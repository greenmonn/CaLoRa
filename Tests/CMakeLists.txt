cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SRC_PATH ${CMAKE_SOURCE_DIR}/../LoRaWan)

add_library(test_target ${SRC_PATH}/List.h ${SRC_PATH}/List.cpp ${SRC_PATH}/SendQueue.h ${SRC_PATH}/SendQueue.cpp)

include_directories(${SRC_PATH})

add_executable(catch_test catch.hpp tests-linkedList.cpp tests-sendqueue.cpp tests-main.cpp)
target_link_libraries(catch_test test_target)