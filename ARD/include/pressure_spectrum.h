#ifndef PRESSURE_SPECTRUM_H
#define PRESSURE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include "fftw_array.h"
#include "pressure_field.h"
#include "size.h"
#include "precision.h"
#include <fftw3.h>

namespace ARD
{
  class PressureField;
  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
  typedef Precision ModeCoefficient;
  typedef boost::shared_ptr<fftw_plan_s> FFTWPlan;

  class PressureSpectrum : public FFTWArray
  {
  public:
    PressureSpectrum(const Size& size);
    PressureSpectrum(const Size& size, const FFTWArrayContent content);
    PressureFieldPointer InverseDCT();
    void Normalize();

  private:
    void Init();
    void InitOutputBuffer();
    void InitPlan();

    FFTWArrayPointer idct_output_buffer_;
    FFTWPlan idct_plan_;
  };  

  typedef boost::shared_ptr<PressureSpectrum> PressureSpectrumPointer;
};

#endif // PRESSURE_SPECTRUM_H
