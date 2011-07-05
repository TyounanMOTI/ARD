#include <force_field.h>

using namespace ARD;

ForceField::ForceField(const Size& size) : FFTWArray(size) {
  Init();
  FillByZero();
}

ForceField::ForceField(const Size& size, const FFTWArrayPointer content) : FFTWArray(size, content) {
  Init();
}

void ForceField::Init() {
  InitOutputBuffer();
  InitPlan();
}

void ForceField::InitOutputBuffer() {
  dct_output_buffer_ = FFTWArrayPointer(new FFTWArray(size()));
}

void ForceField::InitPlan() {
  dct_plan_ = FFTWPlan(fftw_plan_r2r_2d(size().width(), size().height(), get(), dct_output_buffer_->get(), FFTW_REDFT10, FFTW_REDFT10, FFTW_ESTIMATE), fftw_destroy_plan);
}

ForceSpectrumPointer ForceField::DCT() {
  fftw_execute(dct_plan_.get());
  ForceSpectrumPointer output(new ForceSpectrum(size(), dct_output_buffer_));
  output->Normalize();
  return output;
}

void ForceField::EmitSound(const SourcePointer source) {
  set_content(source->position(), Power(source->Pop()));
}
