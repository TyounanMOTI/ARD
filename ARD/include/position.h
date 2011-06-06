#ifndef POSITION_H
#define POSITION_H

namespace ARD
{
  class Position
  {
  public:
    Position(const long x, const long y) : x(x), y(y) {};

  private:
    const long x, y;
  };
};
#endif // POSITION_H