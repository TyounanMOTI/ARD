add_subdirectory(test)

project(2DVisualizer)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

set(2DVisualizer_SRCS
  main.cpp)

if(APPLE)
  list(APPEND 2DVisualizer_SRCS mac/SDLMain.m)
endif(APPLE)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
add_executable(2DVisualizer ${2DVisualizer_SRCS})

if(APPLE)
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
endif(APPLE)

target_link_libraries(2DVisualizer ${SDL_LIBRARY})
