#include <mode_map.h>

using namespace ARD;

Pressure* ModeMap::InverseDCT() {
  return new Pressure(size);
}

Size ModeMap::GetSize() {
  return size;
}
