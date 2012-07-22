#include <SDL.h>
#include <iostream>
#include <algorithm>
#include <ARD.h>

void Quit();

std::unique_ptr<ARD::Scene<ARD::FFTWFloat2DArray> > g_scene;
SDL_Surface* g_surface;
float g_clip = 1.0f;

void Init(int width, int height, int depth=0) {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cerr << "SDL: video init failed" << std::endl;
    Quit();
  }
  g_surface = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

  g_scene.reset(new ARD::Scene<ARD::FFTWFloat2DArray>(boost::extents[height][width], 0.001f));
  std::shared_ptr<ARD::DirectReferenceMicrophone<ARD::FFTWFloat2DArray> > microphone(new ARD::DirectReferenceMicrophone<ARD::FFTWFloat2DArray>());
  std::shared_ptr<ARD::PointSource<ARD::FFTWFloat2DArray> > source(new ARD::PointSource<ARD::FFTWFloat2DArray>({height/2, width/2}, {pow(10.0f, 6), 0.0f, 0.0f}));
  g_scene->AddSource(source);
  g_scene->AddMicrophone(microphone);
}

void Quit() {
  SDL_Quit();
  exit(0);
}

Uint8 quantize(float input, float max) {
  float output = input * 127 / max + 127;

  // hard clip
  if (output > 255) {
    return 255;
  } else if (output < 0) {
    return 0;
  }
  return output;
}

void draw_2D_scalar_field(const ARD::FFTWFloat2DArray& field, float max) {
  for (size_t y = 0; y < field.shape()[0]; y++) {
    for (size_t x = 0; x < field.shape()[1]; x++) {
      Uint8 mono = quantize(field[y][x], max);
      Uint32 color = SDL_MapRGBA(g_surface->format, mono, mono, mono, 0xFF);
      Uint32 *pixel = (Uint32*)g_surface->pixels + y*field.shape()[1] + x;
      *pixel = color;
    }
  }
}

int loop() {
  auto microphones = g_scene->Update();
  std::shared_ptr<ARD::Microphone<ARD::FFTWFloat2DArray> > mic = microphones.front();
  draw_2D_scalar_field(mic->Pop(), g_clip);
  SDL_Flip(g_surface);
  return 1;
}

int SDL_main(int argc, char **argv) {
  int width, height, depth;
  if (argc >= 3) {
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    if (argc >= 4) {
      depth = atoi(argv[3]);
    }
  } else {
    width = 800;
    height = 600;
    depth = 0;
  }

  Init(width, height, depth);

  SDL_Event event;
  Uint8 *keystate;
  while(loop()) {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_KEYDOWN:
	keystate = SDL_GetKeyState(NULL);
	if (keystate[SDLK_UP]) g_clip *= 10.0f;
	else if (keystate[SDLK_DOWN]) g_clip /= 10.0f;
	break;
      case SDL_QUIT:
	Quit();
	break;
      default:
	break;
      }
    }
  }
  Quit();

  return 0;
}
