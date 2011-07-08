#include <whole_field_microphone.h>

using namespace ARD;

const Pressure WholeFieldMicrophone::Pop() {
  content_.pop();
  return Pressure(0.0);
}

void WholeFieldMicrophone::Record(const PressureFieldPointer field) {
  content_.push(PressureFieldPointer(new PressureField(*field)));
}

void WholeFieldMicrophone::Plot(PressureFieldPointer field) {
  PressureFieldPointer front = content_.front();
  Size size = field->size();
  for (int y = 0; y < size.height(); y++) {
    for (int x = 0; x < size.width(); x++) {
      field->set_content(Position(x,y), front->content(Position(x,y)));
    }
  }
  Pop();
}
