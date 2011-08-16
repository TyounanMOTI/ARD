#ifndef DCT_ENGINE_FACTORY_H
#define DCT_ENGINE_FACTORY_H

#include <boost/shared_ptr.hpp>
#include "dct_engine.h"

namespace ARD {
  template<class Precision>
  class DCTEngineFactory
  {
  private:
    typedef boost::shared_ptr<DCTEngine<Precision> > DCTEnginePointer;
  public:
    virtual ~DCTEngineFactory() {};
    virtual DCTEnginePointer GenerateForwardEngine(const Size& size) = 0;
    virtual DCTEnginePointer GenerateBackwardEngine(const Size& size) = 0;
  };
}

#endif // DCT_ENGINE_FACTORY_H
