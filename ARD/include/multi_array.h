#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H

#include <size.h>
#include <fftw3.h>
#include <boost/shared_array.hpp>
#include "position.h"
#include "pressure.h"

namespace ARD
{
  class MultiArray
  {
  public:
    MultiArray() : size_(Size(0,0)) {};
    MultiArray(Size size);
    virtual ~MultiArray();
    Size GetSize();
    Pressure Content(Position position);
    void SetContent(Position position, Pressure input);

  private:
    Size size_;
    fftw_complex* content;
  };
  
  const size_t MultiArrayIndexFromPosition(Position position, Size size);
};

#endif
