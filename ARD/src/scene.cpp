#include <scene.h>
using namespace ARD;

Scene::Scene(const Size& size, const double dt, const DCTEngineFactoryPointer engine_factory) : size_(size) {
  force_field_.reset(new ForceField(size, engine_factory));
  spectrum_pool_.reset(new SpectrumPool(size, dt));
}

MicrophonePointer Scene::Update() {
  force_field_->content()->FillBy(Precision(0));
  source_->Emit(force_field_);
  PressureSpectrumPointer pressure_spectrum(spectrum_pool_->Update(force_field_->DCT()));
  PressureFieldPointer pressure_field(pressure_spectrum->InverseDCT());
  microphone_->Record(pressure_field);
  return microphone_;
}
