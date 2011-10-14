#pragma once

#include <boost/multi_array.hpp>
#include <fftw_float_allocator.h>

namespace ARD {
  typedef boost::multi_array<float, 2, FFTWFloatAllocator> FFTWFloat2DArray;
}
