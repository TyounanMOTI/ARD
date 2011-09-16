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
#include <fftw_dct_engine_factory.h>
#include <math.h>

#ifdef WIN32
#include <winstl/performance/performance_counter.hpp>
using namespace winstl;
#else
#include <unixstl/performance/performance_counter.hpp>
using namespace unixstl;
#endif // WIN32

SDL_Window* g_window;
SDL_Renderer* g_renderer;
SDL_Surface* g_surface;

typedef float Precision;
typedef boost::shared_ptr<ARD::Scene<Precision> > ScenePointer;
typedef boost::shared_ptr<ARD::Microphone<Precision> > MicrophonePointer;
typedef boost::shared_ptr<ARD::WholeFieldMicrophone<Precision> > WholeFieldMicrophonePointer;
typedef boost::shared_ptr<ARD::Source<Precision> > SourcePointer;
typedef boost::shared_ptr<ARD::DCTEngineFactory<Precision> > DCTEngineFactoryPointer;
typedef boost::shared_ptr<ARD::PressureField<Precision> > PressureFieldPointer;
typedef boost::shared_ptr<ARD::ArrayInterface<Precision> > ArrayInterfacePointer;

void draw_pressure_field(Precision* pressure_field, Precision max);

ScenePointer g_scene;
WholeFieldMicrophonePointer g_mic;
SourcePointer g_source;
ARD::Size size;
int width;
int height;
int g_iteration;
int g_zoom;

void Init() {
  g_zoom = 1;
  width = 256;
  height = 256;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_VideoInit(NULL);
  g_window = SDL_CreateWindow("ARD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width/g_zoom, height/g_zoom,
                              SDL_WINDOW_SHOWN);
  //  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
  g_surface = SDL_GetWindowSurface(g_window);

  size = ARD::Size(width, height);
  DCTEngineFactoryPointer engine_factory(new ARD::FFTWDCTEngineFactory<Precision>());
  g_scene.reset(new ARD::Scene<Precision>(size, 1.0f/2000.0f, engine_factory));
  g_mic.reset(new ARD::WholeFieldMicrophone<Precision>());
  g_scene->set_microphone(g_mic);
  std::vector<Precision> sourceContent;
  sourceContent.push_back(10000.0);
  g_source.reset(new ARD::Source<Precision>(ARD::Position(80,100), sourceContent));
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

void capture(int iteration) {
  boost::format f = boost::format("D:\\workspace\\presentation\\intermidiate\\visualizer\\%05d.bmp") % iteration;
  SDL_SaveBMP(g_surface, f.str().c_str());
}

void loop() {
  std::cerr << g_iteration << std::endl;
  performance_counter t;

  static MicrophonePointer mic;

  {
    t.start();

    mic = g_scene->Update();

    t.stop();
    std::cout << t.get_microseconds()/10e6 << std::endl;
  }

  static PressureFieldPointer pressure_field;

  pressure_field.reset(new ARD::PressureField<Precision>(ArrayInterfacePointer(new ARD::FFTWArray<Precision>(size))));
  mic->Plot(pressure_field);
  
  {
    draw_pressure_field(pressure_field->get(), 0.0003f);
    SDL_UpdateWindowSurface(g_window);
  }

//  printf("%.14f\n", pressure_field->content(ARD::Position(180,220)));

//  capture(g_iteration);

  g_iteration++;
}

void draw_pressure_field(Precision* pressure_field, Precision max) {
  for (int y = 0; y < height/g_zoom; y++) {
    for (int x = 0; x < width/g_zoom; x++) {
      Uint8 mono = quantize_to_uint8(pressure_field[(int)floor((Precision)(y*width+x)*g_zoom)], max);
      Uint32 color = SDL_MapRGBA(g_surface->format, mono, mono, mono, 0xFF);
      Uint32* pixel = (Uint32*)g_surface->pixels + y*width + x;
      *pixel = color;
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
  return 0;
}
