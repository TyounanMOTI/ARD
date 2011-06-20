#ifndef PRESSURE_MAP_H
#define PRESSURE_MAP_H

#include <boost/shared_ptr.hpp>
#include "multi_array.h"
#include "pressure_spectrum.h"
#include "size.h"
#include "microphone.h"
#include "pressure.h"
#include <fftw3.h>

namespace ARD
{
  class PressureSpectrum;
  typedef boost::shared_ptr<PressureSpectrum> PressureSpectrumPointer;
  typedef boost::shared_ptr<fftw_plan_s> FFTWPlan;
  
  class PressureField : public MultiArray
  {
  public:
    PressureField(const Size& size);
    PressureField(const Size& size, const MultiArrayContent content);
    PressureSpectrumPointer DCT();
    MicrophonePointer Record(MicrophonePointer microphone) const;

  private:
    void Init();
    void InitOutputBuffer();
    void InitPlan();
    
    MultiArrayPointer dct_output_buffer_;
    FFTWPlan dct_plan_;
  };

  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
};

#endif
