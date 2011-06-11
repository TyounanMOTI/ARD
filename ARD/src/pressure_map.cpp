#include <pressure_map.h>

using namespace ARD;

ModeMapPointer PressureMap::DCT() const {
  return ModeMapPointer(new ModeMap(size()));
}

MicrophonePointer PressureMap::Record(MicrophonePointer microphone) const {
  microphone->Push(content(microphone->position()));
  return microphone;
}
