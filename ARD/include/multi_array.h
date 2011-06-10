#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H

#include <size.h>
#include "position.h"

namespace ARD
{
  class MultiArray
  {
  public:
    MultiArray() : size_(Size(0,0)) {};
    MultiArray(Size size) : size_(size) {};
    Size GetSize();
    double GetData(Position position);

  private:
    Size size_;
  };
};

#endif
