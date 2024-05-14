cmake_minimum_required(VERSION 3.28)
project(lodepng)

set(CMAKE_CXX_STANDARD 26)

add_library(lodepng lodepng.cpp)

target_include_directories(lodepng PUBLIC ./)
