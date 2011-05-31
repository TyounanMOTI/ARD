#include <pressure.h>

using namespace ARD;

Size Pressure::GetSize() {
  return size;
}

ModeMap* Pressure::DCT() {
  return new ModeMap(size);
}
