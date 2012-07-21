cmake_minimum_required(VERSION 2.8)

project(ARD)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
list(APPEND CMAKE_FRAMEWORK_PATH "${CMAKE_SOURCE_DIR}/Frameworks")

find_package(FFTW3 REQUIRED)
find_package(CUDA 4.0)
set(GTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/gtest/include)
add_subdirectory(2DVisualizer)
add_subdirectory(ARD)
add_subdirectory(gtest)
