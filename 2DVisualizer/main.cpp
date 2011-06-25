#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

int main(int argc, char** argv) {
  SDL_Surface* screen;
  SDL_Event event;
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  screen = SDL_SetVideoMode(800, 600, 24, SDL_SWSURFACE);
  
  while(SDL_WaitEvent(&event) >= 0) {
    switch (event.type) {
      case SDL_QUIT: return 0;
      default: break;
    }
  }
  return 0;
}
