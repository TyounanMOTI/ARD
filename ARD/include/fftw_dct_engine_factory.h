#ifndef FFTW_DCT_ENGINE_FACTORY_H
#define FFTW_DCT_ENGINE_FACTORY_H

#include <boost/shared_ptr.hpp>
#include "fftw_dct_engine.h"

namespace ARD {
  class FFTWDCTEngineFactory
  {
  public:
    typedef FFTWDCTEngine::TransformDirection TransformDirection;
      
    FFTWDCTEngineFactory() {};
    FFTWDCTEnginePointer GenerateEngine(const Size& size, const TransformDirection direction);
  };
  typedef boost::shared_ptr<FFTWDCTEngineFactory> FFTWDCTEngineFactoryPointer;
}

#endif // FFTW_DCT_ENGINE_FACTORY_H