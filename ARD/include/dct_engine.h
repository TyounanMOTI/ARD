#pragma once

namespace ARD {
  typedef enum {
    Forward = 0,
    Backward,
  } DCTDirection;

  template <class ArrayType, DCTDirection Direction>
  class DCTEngine {};
}

#include "fftw_dct_engine.h"
