#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include <fftw_array.h>

namespace ARD {
  class Spectrum : public FFTWArray
  {
  public:
    Spectrum(const Size& size) : FFTWArray(size) {};
    Spectrum(const Spectrum& original) : FFTWArray(original) {};
    void Normalize();
  };

  typedef boost::shared_ptr<Spectrum> SpectrumPointer;
};


#endif // SPECTRUM_H