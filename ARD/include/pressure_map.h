#ifndef PRESSURE_MAP_H
#define PRESSURE_MAP_H

#include "mode_map.h"
#include "size.h"

namespace ARD
{
  class ModeMap;
  class PressureMap
  {
  public:
    PressureMap(const Size size) : size(size) {};
    ModeMap* DCT();
    Size GetSize();

  private:
    const Size size;
  };
}

#endif