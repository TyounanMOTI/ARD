#include <microphone.h>

using namespace ARD;

const PressureQueue Microphone::content() const {
  return content_;
}

const Position Microphone::position() const {
  return position_;
}

void Microphone::Push(const Pressure& pressure) {
  content_.push(pressure);
}

const Pressure Microphone::Pop() {
  Pressure result = content_.front();
  content_.pop();
  return result;
}

void Microphone::Record(const PressureFieldPointer field) {
  Push(field->content(position()));
}
