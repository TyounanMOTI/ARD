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
