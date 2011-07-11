#include <spectrum_pool.h>

using namespace ARD;

PressureSpectrumPointer SpectrumPool::Update(const ForceSpectrumPointer forceSpectrum) {
  return PressureSpectrumPointer(new PressureSpectrum(Size(10, 20)));
}
