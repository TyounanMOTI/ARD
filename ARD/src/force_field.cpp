#include <force_field.h>

using namespace ARD;

ForceField::ForceField(const Size& size, const DCTEngineFactoryPointer engine_factory) {
  engine = engine_factory->GenerateForwardEngine(size);
}

ForceSpectrumPointer ForceField::DCT() {
  return ForceSpectrumPointer(new ForceSpectrum(*engine->Execute()));
}
