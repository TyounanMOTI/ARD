#ifndef SIZE_H
#define SIZE_H

namespace ARD
{
  class Size
  {
  public:
    Size(int width, int height) : width(width), height(height) {};
    int width, height;
  };
};

#endif
