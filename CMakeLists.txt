cmake_minimum_required(VERSION 3.12)
project(UnsignedBigInteger)

set(CMAKE_CXX_STANDARD 17)

add_library(CustomInt CustomInt.cpp)

add_executable(play main.cpp)
target_link_libraries(play CustomInt)