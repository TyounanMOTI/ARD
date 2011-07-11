#include <spectrum_pool.h>

using namespace ARD;

PressureSpectrumPointer SpectrumPool::Update(const ForceSpectrumPointer force_spectrum) {
  return PressureSpectrumPointer(new PressureSpectrum(force_spectrum->size()));
}
