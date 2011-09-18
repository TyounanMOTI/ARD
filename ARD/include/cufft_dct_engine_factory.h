#pragma once

#include <boost/shared_ptr.hpp>
#include "dct_engine_factory.h"
#include "cufft_dct_forward_engine.h"

namespace ARD {
  class CufftDCTEngineFactory : public DCTEngineFactory<float>
  {
  private:
    typedef boost::shared_ptr<DCTEngine<float> > DCTEnginePointer;

  public:
    DCTEnginePointer GenerateForwardEngine(const Size& size);
    DCTEnginePointer GenerateBackwardEngine(const Size& size);
  };
}
