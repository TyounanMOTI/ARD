#ifndef PRESSURE_H
#define PRESSURE_H

#include "mode_map.h"
#include "size.h"

namespace ARD
{
  class ModeMap;
  class Pressure
  {
  public:
    Pressure(const Size size) : size(size) {};
    ModeMap* DCT();
    Size GetSize();

  private:
    const Size size;
  };
}

#endif