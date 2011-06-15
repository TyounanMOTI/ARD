#include <pressure_map.h>

using namespace ARD;

PressureMap::PressureMap(const Size& size) : MultiArray(size) {
  dct_output_buffer_ = ModeMapPointer(new ModeMap(size));
  dct_plan_ = FFTWPlan(fftw_plan_r2r_2d(size.width(), size.height(), get(), dct_output_buffer_->get(), FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE), fftw_destroy_plan);
  this->FillByZero();
}

PressureMap::~PressureMap() {
}

ModeMapPointer PressureMap::DCT() const {
  fftw_execute(dct_plan_.get());
  return dct_output_buffer_;
}

MicrophonePointer PressureMap::Record(MicrophonePointer microphone) const {
  microphone->Push(content(microphone->position()));
  return microphone;
}
