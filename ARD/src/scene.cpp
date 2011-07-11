#include <scene.h>
using namespace ARD;

Scene::Scene(const Size& size) : size_(size) {
  force_field_.reset(new ForceField(size));
  spectrum_pool_.reset(new SpectrumPool());
}

MicrophonePointer Scene::Update() {
  force_field_->FillByZero();
  source_->Emit(force_field_);
  PressureSpectrumPointer pressure_spectrum(spectrum_pool_->Update(force_field_->DCT()));
  PressureFieldPointer pressure_field(pressure_spectrum->InverseDCT());
  microphone_->Record(pressure_field);
  return microphone_;
}
