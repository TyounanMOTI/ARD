#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H

#include <size.h>

namespace ARD
{
  class MultiArray
  {
  public:
    MultiArray() : size(Size(0,0)) {};
    MultiArray(Size size) : size(size) {};
    Size GetSize();
    double GetData(const int x, const int y);

  protected:
    Size size;
  };
};

#endif
