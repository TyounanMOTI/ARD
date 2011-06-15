#include <mode_map.h>

using namespace ARD;

PressureMapPointer ModeMap::InverseDCT() const {
  return PressureMapPointer(new PressureMap(size()));
}

void ModeMap::Normalize() {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), content(Position(x,y))/(4*size().Length()));
    }
  }
}