#include <stdlib.h>
#include <boost/random.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include "transforms.h"

void draw();
void put_pixel_mono(SDL_Surface* surface, int x, int y, Uint8 depth);

SDL_Surface* g_screen;
double* map;
int width;
int height;

void Init() {
  width = 800;
  height = 600;
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  g_screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

  boost::minstd_rand gen( 42 );
  boost::uniform_real<> dst( -200, 200 );
  boost::variate_generator<boost::minstd_rand&, boost::uniform_real<>> rand( gen, dst );
  
  map = (double*)malloc(sizeof(double)*width*height);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      map[y*width + x] = rand();
    }
  }
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
    case SDL_KEYDOWN: 
    {
      Uint8* keys = SDL_GetKeyState(NULL);
      if (keys[SDLK_q]) return EXIT;
      break;      
    }
    case SDL_QUIT: return EXIT;
    default: break;
  }
  
  if (SDL_MUSTLOCK(g_screen)) {
    SDL_LockSurface(g_screen);
  }
  
  draw();
  
  if (SDL_MUSTLOCK(g_screen)) {
    SDL_UnlockSurface(g_screen);
  }
  
  SDL_Flip(g_screen);
  
  return CONTINUE;
}

void draw() {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      put_pixel_mono(g_screen, x, y, quantize_to_uint8(map[y*width+x], 200));
    }
  }
}

void put_pixel_mono(SDL_Surface* surface, int x, int y, Uint8 depth) {
  Uint32 mono = SDL_MapRGBA(surface->format, depth, depth, depth, 0);
  Uint32* pixel = (Uint32*)surface->pixels + y*width + x;
  
  *pixel = mono;
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

  free(map);
  return 0;
}
