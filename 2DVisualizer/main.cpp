#include <SDL.h>
#include <iostream>

void Init() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cerr << "SDL: video init failed" << std::endl;
  }
  SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
}

void Quit() {
  SDL_Quit();
  exit(0);
}

int loop() {
  return 1;
}

int SDL_main(int argc, char **argv) {
  Init();

  SDL_Event event;
  while(loop()) {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_QUIT:
	Quit();
	break;
      default:
	break;
      }
    }
  }
  Quit();

  return 0;
}
