#include <microphone.h>

using namespace ARD;

PressureQueue Microphone::Content() {
  return content;
}

void Microphone::Push(Pressure pressure) {
  content.push(pressure);
}
