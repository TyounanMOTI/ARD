#pragma once

#include <boost/multi_array.hpp>
#include "fftw_float_allocator.h"
#include "multi_array.h"

namespace ARD {
  typedef MultiArray<float, 2, FFTWFloatAllocator> FFTWFloat2DArray;
  typedef MultiArray<float, 3, FFTWFloatAllocator> FFTWFloat3DArray;
}
