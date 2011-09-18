#pragma once

#include <boost/shared_ptr.hpp>
#include <fftw3.h>
#include "dct_engine.h"
#include "fftw_array.h"

namespace ARD
{
  template <class Precision, class FFTWPlan>
  class FFTWDCTEngine : public DCTEngine<Precision>
  {
  private:
    typedef boost::shared_ptr<ArrayInterface<Precision> > ArrayInterfacePointer;
    typedef boost::shared_ptr<FFTWArray<Precision> > FFTWArrayPointer;
    
  public:
    enum TransformDirection {
      Forward,
      Backward,
    };

    FFTWDCTEngine(const Size& size, const TransformDirection direction);
    const ArrayInterfacePointer input() const { return input_; }
    const ArrayInterfacePointer Execute();

  private:
    void Normalize();

    FFTWPlan plan_;
    FFTWArrayPointer input_;
    FFTWArrayPointer output_;
    TransformDirection direction_;
  };

  template <class Precision, class FFTWPlan>
  FFTWDCTEngine<Precision, FFTWPlan>::FFTWDCTEngine(const Size& size, const TransformDirection direction) {
    input_.reset(new FFTWArray<double>(size));
    output_.reset(new FFTWArray<double>(size));
    plan_.reset(fftw_plan_r2r_2d(size.height(), size.width(), input_->get(), output_->get(), 
      (fftw_r2r_kind) FFTW_REDFT00, (fftw_r2r_kind) FFTW_REDFT00, FFTW_ESTIMATE),
      fftw_destroy_plan);
    direction_ = direction;
  }

  template <class Precision, class FFTWPlan>
  const boost::shared_ptr<ArrayInterface<Precision> > FFTWDCTEngine<Precision, FFTWPlan>::Execute() {
    fftw_execute(plan_.get());
    if (direction_ == Forward) {
      Normalize();
    }
    return output_;
  }

  template <class Precision, class FFTWPlan>
  void FFTWDCTEngine<Precision, FFTWPlan>::Normalize() {
    (*output_) /= (Precision)4.0*(output_->size().height() - 1)*(output_->size().width() - 1);
  }

  typedef boost::shared_ptr<fftw_plan_s> FFTWDoublePlan;
  typedef boost::shared_ptr<fftwf_plan_s> FFTWFloatPlan;

  template <> FFTWDCTEngine<float, FFTWFloatPlan>::FFTWDCTEngine(const Size& size, const TransformDirection direction);
  template <> const boost::shared_ptr<ArrayInterface<float> > FFTWDCTEngine<float, FFTWFloatPlan>::Execute();
}

