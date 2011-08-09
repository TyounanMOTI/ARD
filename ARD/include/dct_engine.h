#ifndef DCT_ENGINE_H
#define DCT_ENGINE_H

#include <boost/shared_ptr.hpp>
#include "fftw_array.h"

namespace ARD {
  class DCTEngine
  {
  public:
    virtual const FFTWArrayPointer input() const = 0;
    virtual const FFTWArrayPointer Execute() = 0;
  };
  
  typedef boost::shared_ptr<DCTEngine> DCTEnginePointer;
}

#endif // DCT_ENGINE_H
