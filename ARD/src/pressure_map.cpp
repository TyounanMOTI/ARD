#include <pressure_map.h>

using namespace ARD;

ModeMap* PressureMap::DCT() {
  return new ModeMap(size());
}

MicrophonePointer PressureMap::Record(MicrophonePointer microphone) {
  microphone->Push(content(microphone->position()));
  return microphone;
}
