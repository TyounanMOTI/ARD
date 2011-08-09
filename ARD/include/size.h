#ifndef SIZE_H
#define SIZE_H

namespace ARD
{
  class Size
  {
  public:
    Size() : width_(0), height_(0) {};
    Size(int width, int height) : width_(width), height_(height) {};

    int Length() const;
    int width() const;
    int height() const;
    
    bool operator==(const Size& other) const;

  private:
    int width_, height_;
  };
}

#endif // SIZE_H
