#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <string>
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
ARD::SourcePointer g_source;
ARD::Size size;
int width;
int height;
int g_iteration;

void Init() {
  width = 512;
  height = 256;
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  g_screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

  size = ARD::Size(width, height);
  g_scene.reset(new ARD::Scene(size, 0.001));
  g_mic.reset(new ARD::WholeFieldMicrophone());
  g_scene->set_microphone(g_mic);
  std::vector<ARD::Power> sourceContent;
  sourceContent.push_back(ARD::Power(10000.0));
  g_source.reset(new ARD::Source(ARD::Position(100,100), sourceContent));
  g_scene->set_source(g_source);
  
  g_iteration = 0;
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
      Uint8* keys = SDL_GetKeyboardState(NULL);
      if (keys[SDLK_q]) return EXIT;
      break;      
    }
    case SDL_QUIT: return EXIT;
    default: break;
  }
  return CONTINUE;
}

int loop() {
  static ARD::MicrophonePointer mic;
  mic = g_scene->Update();
  static ARD::PressureFieldPointer pressure_field;
  pressure_field.reset(new ARD::PressureField(size));
  mic->Plot(pressure_field);

  if (SDL_MUSTLOCK(g_screen)) {
    SDL_LockSurface(g_screen);
  }
  
  draw_pressure_field(pressure_field->get(), 0.001);

  if (SDL_MUSTLOCK(g_screen)) {
    SDL_UnlockSurface(g_screen);
  }
  
  SDL_Flip(g_screen);
  
/*
  boost::format f = boost::format("/Users/TyounanMOTI/Pictures/visualizer/%05d.bmp") % g_iteration;
  const char* filename = str(f).c_str();
  SDL_SaveBMP(g_screen, filename);
  g_iteration++;
*/

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
