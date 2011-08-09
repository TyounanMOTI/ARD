#ifndef PRESSURE_FIELD_H
#define PRESSURE_FIELD_H

#include <boost/shared_ptr.hpp>
#include "fftw_array.h"
#include "pressure_spectrum.h"
#include "size.h"
#include "pressure.h"
#include <fftw3.h>

namespace ARD
{
  class PressureSpectrum;
  typedef boost::shared_ptr<PressureSpectrum> PressureSpectrumPointer;
  
  class PressureField : public FFTWArray
  {
  public:
    PressureField(const Size& size) : FFTWArray(size) {};
    PressureField(const FFTWArray& original) : FFTWArray(original) {};
  };

  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
}

#endif // PRESSURE_FIELD_H
