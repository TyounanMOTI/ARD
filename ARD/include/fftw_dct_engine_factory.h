#ifndef FFTW_DCT_ENGINE_FACTORY_H
#define FFTW_DCT_ENGINE_FACTORY_H

#include <boost/shared_ptr.hpp>
#include "dct_engine.h"
#include "dct_engine_factory.h"
#include "fftw_dct_engine.h"

namespace ARD {
  class FFTWDCTEngineFactory : public DCTEngineFactory
  {
  public:
    DCTEnginePointer GenerateForwardEngine(const Size& size);
    DCTEnginePointer GenerateBackwardEngine(const Size& size);
  };
  typedef boost::shared_ptr<FFTWDCTEngineFactory> FFTWDCTEngineFactoryPointer;
}

#endif // FFTW_DCT_ENGINE_FACTORY_H
