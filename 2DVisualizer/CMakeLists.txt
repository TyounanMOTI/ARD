project(2DVisualizer)
set(CMAKE_C_COMPILER "gcc-4.7")
set(CMAKE_CXX_COMPILER "g++-4.7")

set(CMAKE_BUILD_TYPE "Debug")

set(2DVisualizer_SRCS
  main.cpp)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/ARD/include)
add_executable(2DVisualizer ${2DVisualizer_SRCS})
set_target_properties(2DVisualizer
  PROPERTIES
  COMPILE_FLAGS "-std=c++11"
  )

if(APPLE)
  add_subdirectory(mac)
  target_link_libraries(2DVisualizer SDLMain)
  set_target_properties(2DVisualizer
    PROPERTIES
    LINK_FLAGS "-Xlinker -rpath -Xlinker @executable_path/../Frameworks/"
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.hirotoshi_yoshitaka.2dvisualizer"
    MACOSX_BUNDLE_BUNDLE_NAME "2DVisualizer.app"
    MACOSX_BUNDLE_COPYRIGHT "Copyright (C) 2012 Hirotoshi YOSHITAKA"
    )
  add_custom_command(TARGET 2DVisualizer POST_BUILD
    COMMAND rsync
    ARGS -ar --delete ${CMAKE_SOURCE_DIR}/Frameworks 2DVisualizer.app/Contents/
    )
  add_custom_target(run_2DVisualizer ALL
    COMMAND open -a 2DVisualizer
    DEPENDS 2DVisualizer
    )
endif(APPLE)

target_link_libraries(2DVisualizer ${SDL_LIBRARY})

add_subdirectory(test)
