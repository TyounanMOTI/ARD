#include <fftw_float_dct_engine.h>

using namespace ARD;

FFTWFloatDCTEngine::FFTWFloatDCTEngine(const Size& size, const TransformDirection direction) {
  input_.reset(new FFTWArray<float>(size));
  output_.reset(new FFTWArray<float>(size));
  plan_.reset(fftwf_plan_r2r_2d(size.height(), size.width(), input_->get(), output_->get(), 
                               (fftw_r2r_kind) direction, (fftw_r2r_kind) direction, FFTW_ESTIMATE),
              fftwf_destroy_plan);
  direction_ = direction;
}

const boost::shared_ptr<ArrayInterface<float> > FFTWFloatDCTEngine::Execute() {
  fftwf_execute(plan_.get());
  if (direction_ == Forward) {
    Normalize();
  }
  return output_;
}

void FFTWFloatDCTEngine::Normalize() {
  (*output_) /= 4.0f*output_->size().Length();
}
