#include <point_microphone.h>

using namespace ARD;

const PressureQueue PointMicrophone::content() const {
  return content_;
}

const Position PointMicrophone::position() const {
  return position_;
}

const Pressure PointMicrophone::Pop() {
  Pressure result = content_.front();
  content_.pop();
  return result;
}

void PointMicrophone::Record(const PressureFieldPointer field) {
  content_.push(field->content(position()));
}
