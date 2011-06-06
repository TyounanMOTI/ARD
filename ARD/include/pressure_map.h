#ifndef PRESSURE_MAP_H
#define PRESSURE_MAP_H

#include <boost/shared_ptr.hpp>
#include "multi_array.h"
#include "mode_map.h"
#include "size.h"
#include "microphone.h"

namespace ARD
{
  class ModeMap;
  class PressureMap : public MultiArray
  {
  public:
    PressureMap(Size size) : MultiArray(size) {};
    ModeMap* DCT();
    MicrophonePointer Record(MicrophonePointer microphone);
  };
}

#endif
