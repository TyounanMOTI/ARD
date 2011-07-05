#ifndef PRESSURE_MAP_H
#define PRESSURE_MAP_H

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
    PressureField(const Size& size, const FFTWArrayPointer content) : FFTWArray(size, content) {};
  };

  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
};

#endif
