#ifndef DCT_ENGINE_H
#define DCT_ENGINE_H

#include <boost/shared_ptr.hpp>
#include "array_interface.h"

namespace ARD {
  class DCTEngine
  {
  public:
    virtual const ArrayInterfacePointer input() const = 0;
    virtual const ArrayInterfacePointer Execute() = 0;
  };
  
  typedef boost::shared_ptr<DCTEngine> DCTEnginePointer;
}

#endif // DCT_ENGINE_H
