#ifndef MODE_MAP_H
#define MODE_MAP_H

#include "pressure.h"
#include "size.h"

namespace ARD
{
  class Pressure;
  class ModeMap
  {
  public:
    ModeMap(Size size) : size(size) {};
    Pressure* InverseDCT();
    Size GetSize();

  private:
    Size size;
  };
}

#endif