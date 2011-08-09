#include <pressure_spectrum.h>

using namespace ARD;

PressureSpectrum::PressureSpectrum(const Size& size, const DCTEngineFactoryPointer engine_factory) {
  engine = engine_factory->GenerateBackwardEngine(size);
}

PressureFieldPointer PressureSpectrum::InverseDCT() {
  return PressureFieldPointer(new PressureField(engine->Execute()));
}
