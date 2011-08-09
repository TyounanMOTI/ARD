#ifndef FORCE_SPECTRUM_H
#define FORCE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include <fftw_array.h>

namespace ARD
{
  class ForceSpectrum : public FFTWArray
  {
  public:
    ForceSpectrum(const Size& size) : FFTWArray(size) {};
    ForceSpectrum(const FFTWArray& original) : FFTWArray(original) {};
    void Normalize(); // deprecated. use: FFTWDCTEngine::Normalize
  };

  typedef boost::shared_ptr<ForceSpectrum> ForceSpectrumPointer;
};

#endif // FORCE_SPECTRUM_H
