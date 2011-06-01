#include <mode_map.h>

using namespace ARD;

PressureMap* ModeMap::InverseDCT() {
  return new PressureMap(size);
}

Size ModeMap::GetSize() {
  return size;
}
