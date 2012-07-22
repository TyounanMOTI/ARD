#include <SDL.h>
#include <iostream>
#include <ARD.h>

void Quit();

void Init(int width, int height, int depth=0) {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cerr << "SDL: video init failed" << std::endl;
    Quit();
  }
  SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
}

void Quit() {
  SDL_Quit();
  exit(0);
}

int loop() {
  return 1;
}

int SDL_main(int argc, char **argv) {
  int width, height, depth;
  if (argc >= 3) {
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    if (argc >= 4) {
      depth = atoi(argv[3]);
    }
  } else {
    width = 800;
    height = 600;
    depth = 0;
  }

  Init(width, height, depth);

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
