cmake_minimum_required(VERSION 3.3)
project(laba3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RK4.cpp RK4.h types.h Point.cpp Point.h myException.cpp myException.h)
add_executable(laba3 ${SOURCE_FILES})