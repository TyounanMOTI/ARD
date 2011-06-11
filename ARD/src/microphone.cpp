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

void Microphone::Pop(const int amount) {
  for (int i = 0; i < amount; i++) {
    content_.pop();
  }
}
