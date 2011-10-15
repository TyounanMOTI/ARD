include_directories(../include)
set(ARD_test_SRCS
  cufft_test.cpp
  fftw_multi_array_test.cpp
  fftw_test.cpp
  gtest_test.cpp
  multi_array_test.cpp
  position_test.cpp
  source_test.cpp
  plot/output_array.cpp)
link_directories(/usr/local/lib)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
cuda_add_executable(ARD_test ${ARD_test_SRCS})
cuda_add_cufft_to_target(ARD_test)
target_link_libraries(ARD_test FFTW3 fftw3f gtest gtest_main)
