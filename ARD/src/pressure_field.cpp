#include <pressure_field.h>

using namespace ARD;

MicrophonePointer PressureField::Record(MicrophonePointer microphone) const {
  microphone->Push(content(microphone->position()));
  return microphone;
}
