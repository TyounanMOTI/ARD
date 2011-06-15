#ifndef PRESSURE_MAP_H
#define PRESSURE_MAP_H

#include <boost/shared_ptr.hpp>
#include "multi_array.h"
#include "mode_map.h"
#include "size.h"
#include "microphone.h"
#include "pressure.h"
#include <fftw3.h>

namespace ARD
{
  class ModeMap;
  typedef boost::shared_ptr<ModeMap> ModeMapPointer;
  typedef boost::shared_ptr<fftw_plan_s> FFTWPlan;
  
  class PressureMap : public MultiArray
  {
  public:
    PressureMap(const Size& size);
    ModeMapPointer DCT();
    MicrophonePointer Record(MicrophonePointer microphone) const;

  private:
    ModeMapPointer dct_output_buffer_;
    FFTWPlan dct_plan_;
  };

  typedef boost::shared_ptr<PressureMap> PressureMapPointer;
};

#endif
