cmake_minimum_required(VERSION 2.8)
project(ARD CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(FFTW3 REQUIRED)
find_package(CUDA REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")

#add_subdirectory(2DVisualizer)
add_subdirectory(ARD)
add_subdirectory(gtest)
