#pragma once
#include "fftw_dct_engine.h"
#include "multi_array.h"

namespace ARD {
  template <class ArrayType>
  class PressureSpectrum {
  public:
    template <class ExtentList>
    PressureSpectrum(const ExtentList& extents, ArrayType& output)
      : _data(extents),
        _dct_engine(_data, output)
    {
      _data.Fill(0);
    }

    const ArrayType& InverseDCT() {
      return _dct_engine.Execute();
    }

    ArrayType _data;

  private:
    DCTEngine<ArrayType, Backward> _dct_engine;
  };
}
