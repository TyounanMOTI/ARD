include_directories(${GTEST_INCLUDE_DIR})
set(2DVisualizerTest_SRCS
#  lambda_test.cpp
  constructor_test.cpp)

add_executable(2DVisualizer_test ${2DVisualizerTest_SRCS})
target_link_libraries(2DVisualizer_test gtest gtest_main)
add_custom_target(run_2DVisualizer_test ALL
  COMMAND 2DVisualizer_test
  DEPENDS 2DVisualizer_test)
