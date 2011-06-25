#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

SDL_Surface* g_screen;

void Init() {
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  g_screen = SDL_SetVideoMode(800, 600, 24, SDL_SWSURFACE);  
}

enum LOOP_EXIT_TYPE{
  CONTINUE = -1,
  EXIT,
  ERROR,
};

// main loop.
// return: > 0   - error
//         == 0  - normal exit
//         == -1 - continue
int loop(SDL_Event* event) {
  switch (event->type) {
    case SDL_QUIT: return EXIT;
    default: break;
  }
  return CONTINUE;
}

int main(int argc, char** argv) {
  Init();

  SDL_Event event;
  int status;
  while(SDL_WaitEvent(&event) >= 0) {
    status = loop(&event);
    if (status != CONTINUE) {
      return status;
    }
  }
  return 0;
}
