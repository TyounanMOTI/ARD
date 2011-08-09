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
  
  class PressureField
  {
  public:
    PressureField(const Size& size) : content_(FFTWArrayPointer(new FFTWArray(size))) {};
    PressureField(const FFTWArrayPointer content) : content_(FFTWArrayPointer(new FFTWArray(*content))) {};
    PressureField(const PressureField& original) : content_(FFTWArrayPointer(new FFTWArray(*original.content_))) {};
    
    const Size size() { return content_->size(); };
    const Precision content(const Position& position) const { return content_->content(position); };
    void set_content(const Position& position, const Precision input) { content_->set_content(position, input); };
    
  private:
    FFTWArrayPointer content_;
  };

  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
}

#endif // PRESSURE_FIELD_H
