#include <mode_map.h>

using namespace ARD;

PressureMapPointer ModeMap::InverseDCT() {
  return PressureMapPointer(new PressureMap(size()));
}
