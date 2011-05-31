#include <mode_map.h>

using namespace ARD;

Pressure* ModeMap::InverseDCT() {
  return new Pressure(width, height);
}

int ModeMap::Size() {
  return width*height;
}
