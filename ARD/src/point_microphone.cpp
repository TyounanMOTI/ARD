#include <point_microphone.h>

using namespace ARD;

const PressureQueue PointMicrophone::content() const {
  return content_;
}

const Position PointMicrophone::position() const {
  return position_;
}

const Pressure PointMicrophone::Pop() {
  if (content_.empty()) {
    return Pressure(0);
  }
  Pressure result = content_.front();
  content_.pop();
  return result;
}

void PointMicrophone::Record(const PressureFieldPointer field) {
  content_.push(field->content(position()));
}

void PointMicrophone::Plot(PressureFieldPointer field) {
  field->set_content(position_, Pop());
}
