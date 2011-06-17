#include <mode_map.h>

using namespace ARD;

ModeMap::ModeMap(const Size& size) : MultiArray(size) {
  Init();
}

ModeMap::ModeMap(const Size& size, const MultiArrayContent content) : MultiArray(size, content) {
  Init();
}

void ModeMap::Init() {
  InitOutputBuffer();
  InitPlan();
}

void ModeMap::InitOutputBuffer() {
  idct_output_buffer_ = MultiArrayPointer(new MultiArray(size()));
}

void ModeMap::InitPlan() {
  idct_plan_ = FFTWPlan(fftw_plan_r2r_2d(size().width(), size().height(), get(), idct_output_buffer_->get(), FFTW_REDFT01, FFTW_REDFT01, FFTW_ESTIMATE), fftw_destroy_plan);
}

PressureMapPointer ModeMap::InverseDCT() {
  fftw_execute(idct_plan_.get());
  PressureMapPointer pressure_map(new PressureMap(size(), idct_output_buffer_->content()));
  return pressure_map;
}

void ModeMap::Normalize() {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), content(Position(x,y))/(4*size().Length()));
    }
  }
}
