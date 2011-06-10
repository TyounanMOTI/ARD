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
  typedef boost::shared_ptr<ModeMap> ModeMapPointer;
  
  class PressureMap : public MultiArray
  {
  public:
    PressureMap(Size size) : MultiArray(size) {};
    ModeMapPointer DCT();
    MicrophonePointer Record(MicrophonePointer microphone);
  };  

  typedef boost::shared_ptr<PressureMap> PressureMapPointer;
};

#endif
