#pragma once

#include <boost/multi_array.hpp>
#include "fftw_float_allocator.h"

namespace ARD {
  template <typename ValueType,
            std::size_t NumDims,
            typename Allocator = std::allocator<ValueType> >
    class MultiArray : public boost::multi_array<ValueType,
                                                 NumDims,
                                                 Allocator>
  {
    typedef boost::multi_array<ValueType, NumDims, Allocator> super_type;

  public:
    MultiArray() : super_type() {}

    template <typename ExtentList>
    explicit MultiArray(const ExtentList& sizes) : super_type(sizes) {}
  };

  typedef MultiArray<float, 2, FFTWFloatAllocator> FFTWFloat2DArray;
}
