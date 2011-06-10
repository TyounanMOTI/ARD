#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H

#include <size.h>

namespace ARD
{
  class MultiArray
  {
  public:
    MultiArray() : size_(Size(0,0)) {};
    MultiArray(Size size) : size_(size) {};
    Size GetSize();
    double GetData(const int x, const int y);

  private:
    Size size_;
  };
};

#endif
