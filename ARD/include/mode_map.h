#ifndef MODE_MAP_H
#define MODE_MAP_H

#include "pressure.h"

namespace ARD
{
  class ModeMap
  {
  public:
    ModeMap(int width, int height) : width(width), height(height) {};
    Pressure* InverseDCT();
    int Size();

  private:
    int width, height;
  };
}

#endif