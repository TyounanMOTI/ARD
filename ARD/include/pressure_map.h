#ifndef PRESSURE_MAP_H
#define PRESSURE_MAP_H

#include "multi_array.h"
#include "mode_map.h"
#include "size.h"

namespace ARD
{
  class ModeMap;
  class PressureMap : public MultiArray
  {
  public:
    PressureMap(Size size) : MultiArray(size) {};
    ModeMap* DCT();
  };
}

#endif