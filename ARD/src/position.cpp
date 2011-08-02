#include <position.h>

using namespace ARD;

long Position::Serialize(const Size& size) {
  return size.width()*y_ + x_;
}
