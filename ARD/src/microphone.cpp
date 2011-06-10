#include <microphone.h>

using namespace ARD;

PressureQueue Microphone::Content() {
  return content;
}

void Microphone::Push(Pressure pressure) {
  content.push(pressure);
}

void Microphone::Pop(const int amount) {
  for (int i = 0; i < amount; i++) {
    content.pop();
  }
}
