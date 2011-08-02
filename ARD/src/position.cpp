#include <position.h>

using namespace ARD;

long Position::Serialize(const Size& size) const {
  return size.width()*y_ + x_;
}
