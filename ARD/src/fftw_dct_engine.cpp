#include <fftw_dct_engine.h>

using namespace ARD;

template <>
FFTWDCTEngine<float, FFTWFloatPlan>::FFTWDCTEngine(const Size& size, const TransformDirection direction) {
  input_.reset(new FFTWArray<float>(size));
  output_.reset(new FFTWArray<float>(size));
  plan_.reset(fftwf_plan_r2r_2d(size.height(), size.width(), input_->get(), output_->get(), 
                               (fftw_r2r_kind) FFTW_REDFT00, (fftw_r2r_kind) FFTW_REDFT00, FFTW_ESTIMATE),
              fftwf_destroy_plan);
  direction_ = direction;
}

template <>
const boost::shared_ptr<ArrayInterface<float> > FFTWDCTEngine<float, FFTWFloatPlan>::Execute() {
  fftwf_execute(plan_.get());
  if (direction_ == Forward) {
    Normalize();
  }
  return output_;
}
