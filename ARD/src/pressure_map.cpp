#include <pressure_map.h>

using namespace ARD;

ModeMapPointer PressureMap::DCT() {
  return ModeMapPointer(new ModeMap(size()));
}

MicrophonePointer PressureMap::Record(MicrophonePointer microphone) {
  microphone->Push(content(microphone->position()));
  return microphone;
}
