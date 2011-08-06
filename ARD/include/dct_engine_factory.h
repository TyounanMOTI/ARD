#ifndef DCT_ENGINE_FACTORY_H
#define DCT_ENGINE_FACTORY_H

#include <boost/shared_ptr.hpp>
#include "dct_engine.h"

namespace ARD {
  class DCTEngineFactory
  {
  public:
    virtual ~DCTEngineFactory() {};
    virtual DCTEnginePointer GenerateForwardEngine(const Size& size) = 0;
    virtual DCTEnginePointer GenerateBackwardEngine(const Size& size) = 0;
  };
  
  typedef boost::shared_ptr<DCTEngineFactory> DCTEngineFactoryPointer;
}

#endif // DCT_ENGINE_FACTORY_H