#include <fftw_dct_engine.h>

using namespace ARD;

FFTWDCTEngine::FFTWDCTEngine(const Size& size, const TransformDirection direction) {
  input_.reset(new FFTWArray(size));
  output_.reset(new FFTWArray(size));
  plan_ = fftw_plan_r2r_2d(size.height(), size.width(), input_->get(), output_->get(), 
                           (fftw_r2r_kind) direction, (fftw_r2r_kind) direction, FFTW_ESTIMATE);
}

void FFTWDCTEngine::Execute() {
  fftw_execute(plan_);
  Normalize();
}

void FFTWDCTEngine::Normalize() {
  for (int y = 0; y < output_->size().height(); y++) {
    for (int x = 0; x < input_->size().width(); x++) {
      output_->set_content(Position(x,y), output_->content(Position(x,y))/(4*output_->size().Length()));
    }
  }
}
