#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H

#include <size.h>
#include <fftw3.h>
#include <boost/shared_array.hpp>
#include "position.h"
#include "pressure.h"

namespace ARD
{
  typedef boost::shared_array<fftw_complex> FFTWComplexArray;
  class MultiArray
  {
  public:
    MultiArray() : size_(Size(0,0)) {};
    MultiArray(Size size);
    virtual ~MultiArray() {};
    
    Size size();
    Pressure content(Position position);
    void set_content(Position position, Pressure input);

  private:
    Size size_;
    FFTWComplexArray content_;
  };
  
  const size_t MultiArrayIndexFromPosition(const Position& position, const Size& size);
};

#endif
