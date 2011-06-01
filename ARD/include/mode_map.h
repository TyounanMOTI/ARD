#ifndef MODE_MAP_H
#define MODE_MAP_H

#include "pressure_map.h"
#include "size.h"

namespace ARD
{
  class PressureMap;
  class ModeMap
  {
  public:
    ModeMap(Size size) : size(size) {};
    PressureMap* InverseDCT();
    Size GetSize();

  private:
    Size size;
  };
}

#endif