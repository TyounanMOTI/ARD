find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
include_directories(../ARD/include /usr/local/include)

include_directories(${GTEST_INCLUDE_DIR})
set(2DVisualizerTest_SRCS
  constructor_test.cpp
  vtk_test.cpp)
add_executable(2DVisualizer_test ${2DVisualizerTest_SRCS})
target_link_libraries(2DVisualizer_test gtest gtest_main vtkHybrid)
add_custom_target(run_2DVisualizer_test ALL
  COMMAND 2DVisualizer_test
  DEPENDS 2DVisualizer_test)

set(2DVisualizer_SRCS
  main.cpp)
add_executable(2DVisualizer ${2DVisualizer_SRCS})
target_link_libraries(2DVisualizer fftw3f vtkHybrid)
add_custom_target(run_2DVisualizer ALL
  COMMAND 2DVisualizer
  DEPENDS 2DVisualizer run_2DVisualizer_test)
