#include <pressure_map.h>

using namespace ARD;

PressureMap::PressureMap(const Size& size) : MultiArray(size) {
  Init();
}

PressureMap::PressureMap(const Size& size, const MultiArrayContent content) : MultiArray(size, content) {
  Init();
}

void PressureMap::Init() {
  InitOutputBuffer();
  InitPlan();
}

void PressureMap::InitOutputBuffer() {
  dct_output_buffer_ = MultiArrayPointer(new MultiArray(size()));
}

void PressureMap::InitPlan() {
  dct_plan_ = FFTWPlan(fftw_plan_r2r_2d(size().width(), size().height(), get(), dct_output_buffer_->get(), FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE), fftw_destroy_plan);
}

ModeMapPointer PressureMap::DCT() {
  fftw_execute(dct_plan_.get());
  ModeMapPointer mode_map = ModeMapPointer(new ModeMap(size(), dct_output_buffer_->content()));
  mode_map->Normalize();
  return mode_map;
}

MicrophonePointer PressureMap::Record(MicrophonePointer microphone) const {
  microphone->Push(content(microphone->position()));
  return microphone;
}
