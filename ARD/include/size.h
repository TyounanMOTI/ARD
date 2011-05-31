#ifndef SIZE_H
#define SIZE_H

namespace ARD
{
  class Size
  {
  public:
    Size() : width(0), height(0) {};
    Size(int width, int height) : width(width), height(height) {};
    
    bool operator==(const Size& other) const;

  private:
    int width, height;
  };
};

#endif
