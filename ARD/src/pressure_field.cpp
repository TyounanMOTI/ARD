#include <pressure_field.h>

using namespace ARD;

PressureField::PressureField(const Size& size) : FFTWArray(size) {
  Init();
}

PressureField::PressureField(const Size& size, const FFTWArrayContent content) : FFTWArray(size, content) {
  Init();
}

void PressureField::Init() {
  InitOutputBuffer();
  InitPlan();
}

void PressureField::InitOutputBuffer() {
  dct_output_buffer_ = FFTWArrayPointer(new FFTWArray(size()));
}

void PressureField::InitPlan() {
  dct_plan_ = FFTWPlan(fftw_plan_r2r_2d(size().width(), size().height(), get(), dct_output_buffer_->get(), FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE), fftw_destroy_plan);
}

PressureSpectrumPointer PressureField::DCT() {
  fftw_execute(dct_plan_.get());
  PressureSpectrumPointer mode_map = PressureSpectrumPointer(new PressureSpectrum(size(), dct_output_buffer_->content()));
  mode_map->Normalize();
  return mode_map;
}

MicrophonePointer PressureField::Record(MicrophonePointer microphone) const {
  microphone->Push(content(microphone->position()));
  return microphone;
}
