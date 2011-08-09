#include <size.h>

using namespace ARD;

bool Size::operator==(const Size& other) const {
  return ((width_ == other.width_) && (height_ == other.height_));
}

