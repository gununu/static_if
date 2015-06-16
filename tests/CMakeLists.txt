cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")
add_executable(out main.cpp)

