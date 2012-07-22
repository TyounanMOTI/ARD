#pragma once
#include "fftw_dct_engine.h"
#include "multi_array.h"

namespace ARD {
  template <class ArrayType>
  class PressureSpectrum {
  public:
    explicit
    PressureSpectrum(ArrayType& output)
      : data_(output.shape()),
        dct_engine_(data_, output)
    {
      data_.Fill(0);
    }

    void InverseDCT() {
      dct_engine_.Execute();
    }

    ArrayType data_;

  private:
    DCTEngine<ArrayType, Backward> dct_engine_;
  };
}
