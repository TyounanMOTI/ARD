#include <size.h>

using namespace ARD;

bool Size::operator==(const Size& other) const {
  return ((width_ == other.width_) && (height_ == other.height_));
}

int Size::Length() const {
  return width_*height_;
}

int Size::width() const {
  return width_;
}

int Size::height() const {
  return height_;
}
