#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <boost/progress.hpp>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include "transforms.h"
#include <scene.h>
#include <whole_field_microphone.h>
#include <math.h>

#ifdef WIN32
#include <winstl/performance/performance_counter.hpp>
using namespace winstl;
#else
#include <unixstl/performance/performance_counter.hpp>
using namepspace unixstl;
#endif // WIN32

void draw_pressure_field(double* pressure_field, double max);

SDL_Window* g_window;
SDL_Renderer* g_renderer;

ARD::ScenePointer g_scene;
ARD::WholeFieldMicrophonePointer g_mic;
ARD::SourcePointer g_source;
ARD::Size size;
int width;
int height;
int g_iteration;
int g_zoom;

void Init() {
  g_zoom = 1;
  width = 512;
  height = 512;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_VideoInit(NULL);
  g_window = SDL_CreateWindow("ARD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width/g_zoom, height/g_zoom,
                              SDL_WINDOW_SHOWN);
  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

  size = ARD::Size(width, height);
  g_scene.reset(new ARD::Scene(size, 1.0/2000.0));
  g_mic.reset(new ARD::WholeFieldMicrophone());
  g_scene->set_microphone(g_mic);
  std::vector<ARD::Power> sourceContent;
  sourceContent.push_back(ARD::Power(10000.0));
  g_source.reset(new ARD::Source(ARD::Position(width/2,height/2), sourceContent));
  g_scene->set_source(g_source);
  
  g_iteration = 0;
}

int Quit(int return_value) {
  SDL_DestroyRenderer(g_renderer);
  SDL_VideoQuit();
  SDL_Quit();
  exit(return_value);
}

enum LOOP_EXIT_TYPE{
  CONTINUE = -1,
  EXIT,
  FAIL,
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

void loop() {
  std::cerr << g_iteration << std::endl;
  performance_counter t;

  static ARD::MicrophonePointer mic;

  {
    t.start();

    mic = g_scene->Update();

    t.stop();
    std::cout << t.get_microseconds()/10e6 << std::endl;
  }

  static ARD::PressureFieldPointer pressure_field;

  pressure_field.reset(new ARD::PressureField(size));
  mic->Plot(pressure_field);
  
  {
    draw_pressure_field(pressure_field->get(), 0.0003);
    SDL_RenderPresent(g_renderer);
  }
/*
  boost::format f = boost::format("/Users/TyounanMOTI/Pictures/visualizer/%05d.bmp") % g_iteration;
  const char* filename = str(f).c_str();
  SDL_SaveBMP(g_screen, filename);
  g_iteration++;
*/

  g_iteration++;
}

void draw_pressure_field(double* pressure_field, double max) {
  for (int y = 0; y < height/g_zoom; y++) {
    for (int x = 0; x < width/g_zoom; x++) {
      Uint8 mono = quantize_to_uint8(pressure_field[(int)floor((double)(y*width+x)*g_zoom)], max);
      SDL_SetRenderDrawColor(g_renderer, mono, mono, mono, 255);
      SDL_RenderDrawPoint(g_renderer, x, y);
    }
  }
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
        Quit(status);
      }
    }

    if (g_iteration > 2000) {
      break;
    }
  }

  Quit(0);
}
