#include <mode_map.h>

using namespace ARD;

PressureMapPointer ModeMap::InverseDCT() const {
  return PressureMapPointer(new PressureMap(size()));
}
