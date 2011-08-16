#include <array_interface.h>

using namespace ARD;

void ArrayInterface::FillByZero() {
  FillBy(Precision_t(0)); 
}

void ArrayInterface::FillBy(const Precision_t& input) {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), input);
    }
  }
}

ArrayInterface& ArrayInterface::operator /= (const ARD::Precision_t rhs) {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), content(Position(x,y))/rhs);
    }
  }
  return *this;
}