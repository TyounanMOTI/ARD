#pragma once

#include "dct_engine.h"
#include "fftw_multi_array.h"
#include "force_field.h"
#include <fftw3.h>

namespace ARD {
  struct FFTWFloatPlanDeleter
  {
    void operator()(fftwf_plan_s* plan) {
      fftwf_destroy_plan(plan);
    }
  };

  typedef std::unique_ptr<fftwf_plan_s, FFTWFloatPlanDeleter> FFTWFloatPlan;

  template <>
  class DCTEngine<FFTWFloat2DArray, Forward>
  {
  public:
    typedef FFTWFloat2DArray Input;
    typedef FFTWFloat2DArray Output;

    explicit DCTEngine(const Input& input)
      : _input(input),
        _output(Output(input.shape())),
        _plan(fftwf_plan_r2r_2d(input.shape()[0],
                               input.shape()[1],
                                const_cast<float*>(input.data()),
                               _output.data(),
                               FFTW_REDFT10,
                               FFTW_REDFT10,
                               FFTW_ESTIMATE
                               ))
    {};

    const Output& Execute() {
      fftwf_execute(_plan.get());
      return _output;
    }

  private:
    const Input& _input;
    Output _output;
    FFTWFloatPlan _plan;
  };
}
