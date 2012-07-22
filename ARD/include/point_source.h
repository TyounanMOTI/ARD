#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include <deque>
#include "source.h"
#include "position.h"

namespace ARD
{
  template <class ArrayType>
  class PointSource : public Source<ArrayType>
  {
  public:
    typedef typename ArrayType::element Precision;
    typedef std::deque<Precision> TimeSeries;

    PointSource(const Position& position, TimeSeries time_series)
      : position_(position), time_series_(time_series) {};

    const Precision Pop() {
      if (time_series_.empty()) {
	return Precision(0.0);
      }
      Precision result = time_series_.front();
      time_series_.pop_front();
      return result;
    }
    
    void Emit(ArrayType& field) {
      field(position_) = Pop();
    }
    
    const Position position() const { return position_; };

  private:
    Position position_;
    TimeSeries time_series_;
  };
}

