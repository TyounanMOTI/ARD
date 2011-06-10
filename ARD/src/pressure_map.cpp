#include <pressure_map.h>

using namespace ARD;

ModeMap* PressureMap::DCT() {
  return new ModeMap(GetSize());
}

MicrophonePointer PressureMap::Record(MicrophonePointer microphone) {
  return microphone;
}
