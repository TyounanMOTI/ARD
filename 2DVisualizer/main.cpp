#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include "transforms.h"
#include <scene.h>
#include <whole_field_microphone.h>

void draw_pressure_field(double* pressure_field, double max);
void put_pixel_mono(SDL_Surface* surface, int x, int y, Uint8 depth);

SDL_Surface* g_screen;
ARD::ScenePointer g_scene;
ARD::WholeFieldMicrophonePointer g_mic;
ARD::Size size;
int width;
int height;

void Init() {
  width = 200;
  height = 200;
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  g_screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

  size = ARD::Size(width, height);
  g_scene.reset(new ARD::Scene(size));
  g_mic.reset(new ARD::WholeFieldMicrophone());
  g_scene->set_microphone(g_mic);
}

enum LOOP_EXIT_TYPE{
  CONTINUE = -1,
  EXIT,
  ERROR,
};

// event.
// return: > 0   - error
//         == 0  - normal exit
//         == -1 - continue
int act_event(SDL_Event* event) {
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
  return CONTINUE;
}

int loop() {
  static ARD::MicrophonePointer mic = g_scene->Update();
  static ARD::PressureFieldPointer dummy_field(new ARD::PressureField(size));
  dummy_field->set_content(ARD::Position(10,20), ARD::Pressure(0.0001));
  mic->Record(dummy_field);
  static ARD::PressureFieldPointer pressure_field(new ARD::PressureField(size));
  mic->Plot(pressure_field);

  if (SDL_MUSTLOCK(g_screen)) {
    SDL_LockSurface(g_screen);
  }
  
  draw_pressure_field(pressure_field->get(), 0.0001);

  if (SDL_MUSTLOCK(g_screen)) {
    SDL_UnlockSurface(g_screen);
  }
  
  SDL_Flip(g_screen);

  return 0;
}

void draw_pressure_field(double* pressure_field, double max) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      put_pixel_mono(g_screen, x, y, quantize_to_uint8(pressure_field[y*width+x], max));
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

  while(1) {
    loop();
    while (SDL_PollEvent(&event)) {
      status = act_event(&event);
      if (status != CONTINUE) {
        return status;
      }
    }
  }

  return 0;
}
