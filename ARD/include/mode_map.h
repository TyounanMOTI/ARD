#ifndef MODE_MAP_H
#define MODE_MAP_H

#include "multi_array.h"
#include "pressure_map.h"
#include "size.h"

namespace ARD
{
  class PressureMap;
  class ModeMap : public MultiArray
  {
  public:
    ModeMap(Size size) : MultiArray(size) {};
    PressureMap* InverseDCT();
  };
}

#endif
