#pragma once

#include <boost/multi_array.hpp>
#include <boost/strong_typedef.hpp>

namespace ARD {
  BOOST_STRONG_TYPEDEF(float, fftwFloat);
  typedef boost::multi_array<fftwFloat, 2> FFTWFloat2DArray;
}
