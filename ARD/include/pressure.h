#ifndef PRESSURE_H
#define PRESSURE_H

namespace ARD
{
  class Pressure
  {
  public:
    Pressure(int width, int height) : width(width), height(height) {};
    int Size();

  private:
    int width, height;
  };
}

#endif