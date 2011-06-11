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
    
    const Size size() const;
    const Pressure content(const Position& position) const;
    void set_content(const Position& position, const Pressure& input);

  private:
    const Size size_;
    FFTWComplexArray content_;
  };
  
  const size_t MultiArrayIndexFromPosition(const Position& position, const Size& size);
};

#endif
