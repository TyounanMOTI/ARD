#ifndef PRESSURE_SPECTRUM_H
#define PRESSURE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include "spectrum.h"
#include "pressure_field.h"
#include "size.h"
#include "fftw_plan.h"
#include <fftw3.h>

namespace ARD
{
  class PressureField;
  typedef boost::shared_ptr<PressureField> PressureFieldPointer;

  class PressureSpectrum : public Spectrum
  {
  public:
    PressureSpectrum(const Size& size);
    PressureSpectrum(const Size& size, const FFTWArrayContent content);
    PressureFieldPointer InverseDCT();

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
