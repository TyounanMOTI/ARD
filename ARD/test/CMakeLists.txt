include_directories(../include ${GTEST_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

set(ARD_test_SRCS
  cufft_test.cpp
  fftw_dct_engine_test.cpp
  fftw_multi_array_test.cpp
  fftw_test.cpp
  gtest_test.cpp
  multi_array_test.cpp
  position_test.cpp
  scene_test.cpp
  point_source_test.cpp
  valarray_test.cpp
  direct_reference_microphone.cpp
  plot/output_array.cpp)
  
if(CUDA_FOUND)
  add_definitions(-DCUDA) # disable for system without CUDA GPU
  cuda_add_executable(ARD_test ${ARD_test_SRCS})
  cuda_add_cufft_to_target(ARD_test)
else(CUDA_FOUND)
  add_executable(ARD_test ${ARD_test_SRCS})
endif(CUDA_FOUND)

target_link_libraries(ARD_test ${FFTW3_LIBRARIES} gtest gtest_main)
add_custom_target(run_ARD_test ALL
  COMMAND ARD_test
  DEPENDS ARD_test)

if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.7")
  set_target_properties(ARD_test
    PROPERTIES
    COMPILE_FLAGS "-std=c++11"
    )
else(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.7")
  set_target_properties(ARD_test
    PROPERTIES
    COMPILE_FLAGS "-std=gnu++0x"
    )
endif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.7")