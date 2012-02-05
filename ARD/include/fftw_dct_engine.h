#pragma once

#include "dct_engine.h"
#include "fftw_multi_array.h"
#include <fftw3.h>
#include <vector>

namespace ARD {
  struct FFTWFloatPlanDeleter
  {
    void operator()(fftwf_plan_s* plan) {
      fftwf_destroy_plan(plan);
    }
  };

  typedef std::unique_ptr<fftwf_plan_s, FFTWFloatPlanDeleter> FFTWFloatPlan;

  template <std::size_t NumDims>
  class DCTEngine<MultiArray<float, NumDims, FFTWFloatAllocator>, Forward>
  {
  public:
    typedef MultiArray<float, NumDims, FFTWFloatAllocator> ArrayType;
    typedef ArrayType Input;
    typedef ArrayType Output;

    explicit DCTEngine(const Input& input)
      : _input(input),
        _output(input.shape()),
        _normalization_factor(input.num_elements() * pow(2, NumDims))
    {
      std::array<int, NumDims> shape;
      std::copy_n(input.shape().begin(), NumDims, shape.begin());
      std::vector<fftw_r2r_kind> kind(NumDims, FFTW_REDFT10);
      _plan.reset(fftwf_plan_r2r(NumDims,
                                 shape.data(),
                                 const_cast<float*>(input.data()),
                  _output.data(),
                  kind.data(),
                  FFTW_MEASURE));
    }

    const Output& Execute() {
      fftwf_execute(_plan.get());
      _output /= _normalization_factor;
      return _output;
    }

  private:
    const Input& _input;
    Output _output;
    const float _normalization_factor;
    FFTWFloatPlan _plan;
  };

  template<std::size_t NumDims>
  class DCTEngine<MultiArray<float, NumDims, FFTWFloatAllocator>, Backward>
  {
  public:
    typedef MultiArray<float, NumDims, FFTWFloatAllocator> ArrayType;
    typedef ArrayType Input;
    typedef ArrayType Output;

    DCTEngine(const Input& input, Output& output)
      : _input(input),
        _output(output)
    {
      std::array<int, NumDims> shape;
      std::copy_n(input.shape().begin(), NumDims, shape.begin());
      std::vector<fftw_r2r_kind> kind(NumDims, FFTW_REDFT01);
      _plan.reset(fftwf_plan_r2r(NumDims,
                                 shape.data(),
                                 const_cast<float*>(input.data()),
                                 _output.data(),
                                 kind.data(),
                                 FFTW_MEASURE));
    }

    const Output& Execute() {
      fftwf_execute(_plan.get());
      return _output;
    }

  private:
    const Input& _input;
    Output& _output;
    FFTWFloatPlan _plan;
  };
}
