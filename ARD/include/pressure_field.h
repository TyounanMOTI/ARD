#ifndef PRESSURE_FIELD_H
#define PRESSURE_FIELD_H

#include <boost/shared_ptr.hpp>
#include "array_interface.h"
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
    PressureField(const PressureField& original) : content_(original.content_->Clone()) {};
    explicit PressureField(const ArrayInterfacePointer content) : content_(content->Clone()) {};
    
    Precision_t* get() const { return content_->get(); }
    const Size size() const { return content_->size(); };
    const Precision_t content(const Position& position) const { return content_->content(position); };
    void set_content(const Position& position, const Precision_t input) { content_->set_content(position, input); };
    
  private:
    ArrayInterfacePointer content_;
  };

  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
}

#endif // PRESSURE_FIELD_H
