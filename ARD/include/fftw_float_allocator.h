#pragma once

#include <fftw3.h>
#include <fftw_multi_array.h>

namespace ARD {
  BOOST_STRONG_TYPEDEF(float, fftwFloat);
}

typedef std::allocator<ARD::fftwFloat> fftwFloatAllocator;

template <>
fftwFloatAllocator::pointer fftwFloatAllocator::allocate(fftwFloatAllocator::size_type num, std::allocator<void>::const_pointer hint = 0) {
  return (pointer)( fftwf_malloc(num * sizeof(ARD::fftwFloat)) );
}

template <>
void fftwFloatAllocator::deallocate(fftwFloatAllocator::pointer p, fftwFloatAllocator::size_type) {
  fftwf_free(p);
}
