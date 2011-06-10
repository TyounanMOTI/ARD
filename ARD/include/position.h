#ifndef POSITION_H
#define POSITION_H

namespace ARD
{
  class Position
  {
  public:
    Position(const long x, const long y) : x_(x), y_(y) {};

  private:
    const long x_, y_;
  };
};

#endif //POSITION_H
