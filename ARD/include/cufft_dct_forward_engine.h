#pragma once

#include "dct_engine.h"
#include "cufft_real_array.h"

namespace ARD {
  class CufftDCTForwardEngine : public DCTEngine<float>
  {
  private:
    typedef boost::shared_ptr<ArrayInterface<float> > ArrayInterfacePointer;
    typedef boost::shared_ptr<CufftRealArray> CufftRealArrayPointer;

  public:
    explicit CufftDCTForwardEngine(const Size& size);
    const ArrayInterfacePointer input() const { return input_; }
    const ArrayInterfacePointer Execute() { return input_; }

  private:
    CufftRealArrayPointer input_;
  };
}
