#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include <deque>
#include "position.h"

namespace ARD
{
  template <class Precision>
  class PointSource
  {
  public:
    typedef std::deque<Precision> Content;

    PointSource(const Position& position, Content content);
    const Precision Pop();
    template <class ArrayType> void Emit(ArrayType& field);
    const Position position() const { return position_; };

  private:
    Position position_;
    Content content_;
  };

  template <class Precision>
  PointSource<Precision>::PointSource(const Position& position, Content content) : position_(position), content_(content) {};

  template <class Precision>
  const Precision PointSource<Precision>::Pop() {
    if (content_.empty()) {
      return Precision(0.0);
    }
    Precision result = content_.front();
    content_.pop_front();
    return result;
  }

  template <class Precision> template <class ArrayType>
  void PointSource<Precision>::Emit(ArrayType& field) {
    field(position_) = Pop();
  }
}

