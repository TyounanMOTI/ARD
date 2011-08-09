#ifndef POSITION_H
#define POSITION_H

#include "size.h"

namespace ARD
{
  class Position
  {
  public:
    Position() : x_(0), y_(0) {};
    Position(const long x, const long y) : x_(x), y_(y) {};
    long x() const { return x_; };
    long y() const { return y_; };
    long Serialize(const Size& size) const;

  private:
    long x_, y_;
  };
}

#endif //POSITION_H
