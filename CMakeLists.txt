cmake_minimum_required(VERSION 2.8)
project(ARD CXX)
include(FindFFTW3.cmake)

add_library(fftw3f SHARED IMPORTED)
set_property(TARGET fftw3f PROPERTY IMPORTED_LOCATION /usr/local/lib/libfftw3f.dylib)
#find_package(FFTW3 REQUIRED)
find_package(CUDA REQUIRED)

#add_subdirectory(2DVisualizer)
add_subdirectory(ARD)
add_subdirectory(gtest)
