#include <array_interface.h>

using namespace ARD;

void ArrayInterface::FillByZero() {
  FillBy(Precision(0)); 
}

void ArrayInterface::FillBy(const Precision& input) {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), input);
    }
  }
}
