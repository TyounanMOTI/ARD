#ifndef SIZE_H
#define SIZE_H

namespace ARD
{
  class Size
  {
  public:
    Size() : width_(0), height_(0) {};
    Size(int width, int height) : width_(width), height_(height) {};

    int Length() const { return width_*height_; };
    int width() const { return width_; };
    int height() const { return height_; };
    
    bool operator==(const Size& other) const;

  private:
    int width_, height_;
  };
}

#endif // SIZE_H
