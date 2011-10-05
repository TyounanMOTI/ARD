#pragma once

#include <boost/multi_array.hpp>
#include <boost/strong_typedef.hpp>
#include <fftw_float_allocator.h>

namespace ARD {
  typedef boost::multi_array<fftwFloat, 2> FFTWFloat2DArray;
}
