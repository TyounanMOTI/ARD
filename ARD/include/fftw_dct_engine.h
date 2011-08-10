#ifndef FFTW_DCT_ENGINE_H
#define FFTW_DCT_ENGINE_H

#include <boost/shared_ptr.hpp>
#include <fftw3.h>
#include "dct_engine.h"
#include "fftw_array.h"

namespace ARD
{
  class FFTWDCTEngine : public DCTEngine
  {
  public:
    enum TransformDirection {
      Forward = FFTW_REDFT10,
      Backward = FFTW_REDFT01,
    };

    FFTWDCTEngine(const Size& size, const TransformDirection direction);
    const ArrayInterfacePointer input() const { return input_; }
    const ArrayInterfacePointer Execute();

  private:
    void Normalize();

    fftw_plan plan_;
    FFTWArrayPointer input_;
    FFTWArrayPointer output_;
    TransformDirection direction_;
  };

  typedef boost::shared_ptr<FFTWDCTEngine> FFTWDCTEnginePointer;
}

#endif // FFTW_DCT_ENGINE_H
