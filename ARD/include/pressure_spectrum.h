#ifndef PRESSURE_SPECTRUM_H
#define PRESSURE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include "multi_array.h"
#include "pressure_map.h"
#include "size.h"
#include "precision.h"
#include <fftw3.h>

namespace ARD
{
  class PressureMap;
  typedef boost::shared_ptr<PressureMap> PressureMapPointer;
  typedef Precision ModeCoefficient;
  typedef boost::shared_ptr<fftw_plan_s> FFTWPlan;

  class PressureSpectrum : public MultiArray
  {
  public:
    PressureSpectrum(const Size& size);
    PressureSpectrum(const Size& size, const MultiArrayContent content);
    PressureMapPointer InverseDCT();
    void Normalize();

  private:
    void Init();
    void InitOutputBuffer();
    void InitPlan();

    MultiArrayPointer idct_output_buffer_;
    FFTWPlan idct_plan_;
  };  

  typedef boost::shared_ptr<PressureSpectrum> PressureSpectrumPointer;
};

#endif // PRESSURE_SPECTRUM_H
