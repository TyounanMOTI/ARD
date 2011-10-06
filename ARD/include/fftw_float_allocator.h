#pragma once

#include <fftw3.h>
#include <fftw_multi_array.h>

namespace ARD {
  BOOST_STRONG_TYPEDEF(float, fftwFloat);
}

typedef std::allocator<ARD::fftwFloat> FFTWFloatAllocator;

template <>
FFTWFloatAllocator::pointer FFTWFloatAllocator::allocate(size_type num) {
  return (pointer)( fftwf_malloc(num * sizeof(ARD::fftwFloat)) );
}

template <>
FFTWFloatAllocator::pointer FFTWFloatAllocator::allocate(FFTWFloatAllocator::size_type num, std::allocator<void>::const_pointer hint) {
  return allocate(num);
}

template <>
void FFTWFloatAllocator::deallocate(FFTWFloatAllocator::pointer p, FFTWFloatAllocator::size_type) {
  fftwf_free(p);
}
