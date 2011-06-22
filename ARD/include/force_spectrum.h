#ifndef FORCE_SPECTRUM_H
#define FORCE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include <spectrum.h>

namespace ARD
{
  class ForceSpectrum : public Spectrum
  {
  public:
    ForceSpectrum(const Size& size, const FFTWArrayContent content) : Spectrum(size, content) {};
  };

  typedef boost::shared_ptr<ForceSpectrum> ForceSpectrumPointer;
};

#endif // FORCE_SPECTRUM_H
