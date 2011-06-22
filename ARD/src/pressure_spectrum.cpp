#include <pressure_spectrum.h>

using namespace ARD;

PressureSpectrum::PressureSpectrum(const Size& size) : FFTWArray(size) {
  Init();
}

PressureSpectrum::PressureSpectrum(const Size& size, const FFTWArrayContent content) : FFTWArray(size, content) {
  Init();
}

void PressureSpectrum::Init() {
  InitOutputBuffer();
  InitPlan();
}

void PressureSpectrum::InitOutputBuffer() {
  idct_output_buffer_ = FFTWArrayPointer(new FFTWArray(size()));
}

void PressureSpectrum::InitPlan() {
  idct_plan_ = FFTWPlan(fftw_plan_r2r_2d(size().width(), size().height(), get(), idct_output_buffer_->get(), FFTW_REDFT01, FFTW_REDFT01, FFTW_ESTIMATE), fftw_destroy_plan);
}

PressureFieldPointer PressureSpectrum::InverseDCT() {
  fftw_execute(idct_plan_.get());
  PressureFieldPointer pressure_field(new PressureField(size(), idct_output_buffer_->content()));
  return pressure_field;
}

void PressureSpectrum::Normalize() {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), content(Position(x,y))/(4*size().Length()));
    }
  }
}
