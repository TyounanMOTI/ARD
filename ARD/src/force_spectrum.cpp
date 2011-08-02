#include <force_spectrum.h>

using namespace ARD;

void ForceSpectrum::Normalize() {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), content(Position(x,y))/(4*size().Length()));
    }
  }
}
