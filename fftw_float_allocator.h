#pragma once

#include <fftw3.h>

namespace ARD {
  class FFTWFloatAllocator : public std::allocator<float>
  {
  public:
    typedef size_t size_type;
    typedef float* pointer;

    pointer allocate(size_type num, const void* h = 0) {
      return static_cast<pointer>(fftwf_malloc(sizeof(float)*num));
    }

    void deallocate(pointer p, size_type) {
      fftwf_free(p);
    }
  };
}
