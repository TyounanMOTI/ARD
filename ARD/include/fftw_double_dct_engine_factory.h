#ifndef FFTW_DOUBLE_DCT_ENGINE_FACTORY_H
#define FFTW_DOUBLE_DCT_ENGINE_FACTORY_H

#include <boost/shared_ptr.hpp>
#include "dct_engine.h"
#include "dct_engine_factory.h"
#include "fftw_double_dct_engine.h"

namespace ARD {
  class FFTWDoubleDCTEngineFactory : public DCTEngineFactory<double>
  {
  private:
    typedef boost::shared_ptr<DCTEngine<double> > DCTEnginePointer;
  public:
    DCTEnginePointer GenerateForwardEngine(const Size& size);
    DCTEnginePointer GenerateBackwardEngine(const Size& size);
  };
}

#endif // FFTW_DOUBLE_DCT_ENGINE_FACTORY_H
