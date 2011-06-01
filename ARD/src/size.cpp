#include <size.h>

using namespace ARD;

bool Size::operator==(const Size& other) const {
  return ((width == other.width) && (height == other.height));
}

int Size::Length() {
  return width*height;
}
