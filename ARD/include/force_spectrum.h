#ifndef FORCE_SPECTRUM_H
#define FORCE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include <fftw_array.h>

namespace ARD
{
  class ForceSpectrum
  {
  public:
    ForceSpectrum(const FFTWArrayPointer content) : content_(FFTWArrayPointer(new FFTWArray(*content))) {};
    const Size size() const { return content_->size(); };
    const Precision content(const Position& position) const { return content_->content(position); };
    
  private:
    FFTWArrayPointer content_;
  };

  typedef boost::shared_ptr<ForceSpectrum> ForceSpectrumPointer;
}

#endif // FORCE_SPECTRUM_H
