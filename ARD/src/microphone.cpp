#include <microphone.h>

using namespace ARD;

PressureQueue Microphone::Content() {
  return content_;
}

const Position Microphone::position() {
  return position_;
}

void Microphone::Push(Pressure pressure) {
  content_.push(pressure);
}

void Microphone::Pop(const int amount) {
  for (int i = 0; i < amount; i++) {
    content_.pop();
  }
}
