#ifndef PRESSURE_H
#define PRESSURE_H

#include "mode_map.h"

namespace ARD
{
  class ModeMap;
  class Pressure
  {
  public:
    Pressure(int width, int height) : width(width), height(height) {};
    ModeMap* DCT();
    int Size();

  private:
    int width, height;
  };
}

#endif