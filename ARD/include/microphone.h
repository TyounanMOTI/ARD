#pragma once

#include <boost/shared_ptr.hpp>

namespace ARD
{
  template <class ArrayType>
  class Microphone
  {
  public:
    Microphone() {};
    virtual void Record(const ArrayType& input) = 0;
    virtual ArrayType Pop() = 0;
    virtual ~Microphone() {};
  };
}
