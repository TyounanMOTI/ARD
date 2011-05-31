#ifndef MODE_MAP_H
#define MODE_MAP_H

#include "pressure.h"

namespace ARD
{
  class ModeMap
  {
  public:
    Pressure* InverseDCT();
    int Size();
  };
}

#endif