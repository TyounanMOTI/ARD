#include <pressure_spectrum.h>

using namespace ARD;

PressureSpectrum::PressureSpectrum(const Size& size) : FFTWArray(size) {
  Init();
  FillByZero();
}

PressureSpectrum::PressureSpectrum(const PressureSpectrum& original) : FFTWArray(original) {
  Init();
}

void PressureSpectrum::Init() {
  InitOutputBuffer();
  InitPlan();
}

void PressureSpectrum::InitOutputBuffer() {
  idct_output_buffer_ = PressureFieldPointer(new PressureField(size()));
}

void PressureSpectrum::InitPlan() {
  idct_plan_ = FFTWPlan(fftw_plan_r2r_2d(size().height(), size().width(), get(), idct_output_buffer_->get(), FFTW_REDFT01, FFTW_REDFT01, FFTW_ESTIMATE), fftw_destroy_plan);
}

PressureFieldPointer PressureSpectrum::InverseDCT() {
  fftw_execute(idct_plan_.get());
  PressureFieldPointer pressure_field(new PressureField(*idct_output_buffer_));
  return pressure_field;
}
