#include <whole_field_microphone.h>

using namespace ARD;

const PressureFieldPointer WholeFieldMicrophone::Pop() {
  PressureFieldPointer result(content_.front());
  content_.pop();
  return result;
}

void WholeFieldMicrophone::Record(const PressureFieldPointer field) {
  content_.push(PressureFieldPointer(new PressureField(*field)));
}

void WholeFieldMicrophone::Plot(PressureFieldPointer field) {
  PressureFieldPointer front = Pop();
  Size size = field->size();
  for (int y = 0; y < size.height(); y++) {
    for (int x = 0; x < size.width(); x++) {
      field->set_content(Position(x,y), front->content(Position(x,y)));
    }
  }
}
