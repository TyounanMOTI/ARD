#include <pressure_map.h>

using namespace ARD;

Size PressureMap::GetSize() {
  return size;
}

ModeMap* PressureMap::DCT() {
  return new ModeMap(size);
}
