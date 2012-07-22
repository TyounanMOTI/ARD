set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
project(2DVisualizer_mac)

add_library(SDLMain STATIC SDLMain.m)
target_link_libraries(SDLMain ${SDL_LIBRARY})
