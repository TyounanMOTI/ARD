#include <mode_map.h>

using namespace ARD;

PressureMap* ModeMap::InverseDCT() {
  return new PressureMap(GetSize());
}
