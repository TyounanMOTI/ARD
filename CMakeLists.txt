cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
list(APPEND CMAKE_FRAMEWORK_PATH "${CMAKE_SOURCE_DIR}/Frameworks")

find_package(FFTW3 REQUIRED)
find_package(CUDA 4.0 QUIET)
set(GTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/gtest/include)
add_subdirectory(2DVisualizer)
add_subdirectory(ARD)
add_subdirectory(gtest)
