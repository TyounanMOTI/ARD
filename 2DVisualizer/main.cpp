#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

int main(int argc, char** argv) {
  SDL_Surface* screen;
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  screen = SDL_SetVideoMode(800, 600, 24, SDL_SWSURFACE);
  while(1);
  return 0;
}
