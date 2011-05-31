#include <pressure.h>

using namespace ARD;

int Pressure::Size() {
  return width*height;
}

ModeMap* Pressure::DCT() {
  return new ModeMap(width, height);
}
