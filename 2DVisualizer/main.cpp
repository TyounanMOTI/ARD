#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include "transforms.h"
#include <scene.h>
#include <whole_field_microphone.h>

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

void Init() {
  width = 512;
  height = 256;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_VideoInit(NULL);
  g_window = SDL_CreateWindow("ARD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);
  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

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

int Quit(int return_value) {
  SDL_DestroyRenderer(g_renderer);
  SDL_VideoQuit();
  SDL_Quit();
  return return_value;
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

void loop() {
  static ARD::MicrophonePointer mic;
  {
    boost::timer t;
    mic = g_scene->Update();
    std::cout << "Update(): " << t.elapsed() << std::endl;
  }
  static ARD::PressureFieldPointer pressure_field;

  pressure_field.reset(new ARD::PressureField(size));
  mic->Plot(pressure_field);
  
  {
    boost::timer t;
    draw_pressure_field(pressure_field->get(), 0.001);
  
    SDL_RenderPresent(g_renderer);
    std::cout << "Render: " << t.elapsed() << std::endl;
  }
/*
  boost::format f = boost::format("/Users/TyounanMOTI/Pictures/visualizer/%05d.bmp") % g_iteration;
  const char* filename = str(f).c_str();
  SDL_SaveBMP(g_screen, filename);
  g_iteration++;
*/

}

void draw_pressure_field(double* pressure_field, double max) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Uint8 mono = quantize_to_uint8(pressure_field[y*width+x], max);
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
  }

  Quit(0);
}
