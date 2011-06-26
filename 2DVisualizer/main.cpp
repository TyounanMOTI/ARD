#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

void draw();
void put_pixel_mono(SDL_Surface* surface, int x, int y, Uint8 depth);

SDL_Surface* g_screen;

void Init() {
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  g_screen = SDL_SetVideoMode(800, 600, 24, SDL_HWSURFACE|SDL_DOUBLEBUF);
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
  put_pixel_mono(g_screen, 10, 10, 128);
}

void put_pixel_mono(SDL_Surface* surface, int x, int y, Uint8 depth) {
  Uint32 mono = SDL_MapRGBA(surface->format, depth, depth, depth, depth);
  Uint32* pixel = (Uint32*)surface->pixels + y*surface->pitch + x*surface->format->BitsPerPixel;
  
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
  return 0;
}
