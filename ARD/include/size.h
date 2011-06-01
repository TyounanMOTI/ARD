#ifndef SIZE_H
#define SIZE_H

namespace ARD
{
  class Size
  {
  public:
    Size() : width(0), height(0) {};
    Size(int width, int height) : width(width), height(height) {};

    int Length();
    
    bool operator==(const Size& other) const;

  private:
    int width, height;
  };
};

#endif
