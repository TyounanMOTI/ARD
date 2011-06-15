#include <pressure_map.h>

using namespace ARD;

PressureMap::PressureMap(const Size& size) : MultiArray(size) {
  dct_output_buffer_ = ModeMapPointer(new ModeMap(size));
  dct_plan_ = fftw_plan_r2r_2d(size.width(), size.height(), get(), dct_output_buffer_->get(), FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE);
  this->FillByZero();
}

PressureMap::~PressureMap() {
  fftw_destroy_plan(dct_plan_);
}

ModeMapPointer PressureMap::DCT() const {
  fftw_execute(dct_plan_);
  return dct_output_buffer_;
}

MicrophonePointer PressureMap::Record(MicrophonePointer microphone) const {
  microphone->Push(content(microphone->position()));
  return microphone;
}
