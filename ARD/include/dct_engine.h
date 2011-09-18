#ifndef DCT_ENGINE_H
#define DCT_ENGINE_H

#include <boost/shared_ptr.hpp>
#include "array_interface.h"

namespace ARD {
  template <class Precision>
  class DCTEngine
  {
  private:
    typedef boost::shared_ptr<ArrayInterface<Precision> > ArrayInterfacePointer; 
  public:
    virtual ~DCTEngine() {};
    virtual const ArrayInterfacePointer input() const = 0;
    virtual const ArrayInterfacePointer Execute() = 0;
  };
}

#endif // DCT_ENGINE_H
