#pragma once
#include <vector>

namespace ARD {
  template <class ArrayType>
  class Source
  {
  public:
    Source() {}
    virtual ~Source() {}

    virtual void Emit(ArrayType& target) = 0;
  };
}
