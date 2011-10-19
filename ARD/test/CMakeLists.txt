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
cuda_add_executable(ARD_test ${ARD_test_SRCS})
cuda_add_cufft_to_target(ARD_test)
target_link_libraries(ARD_test fftw3 fftw3f gtest gtest_main)
add_custom_target(run_ARD_test ALL
  COMMAND ARD_test
  DEPENDS ARD_test)