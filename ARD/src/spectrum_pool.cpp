#include <spectrum_pool.h>

using namespace ARD;

PressureSpectrumPointer SpectrumPool::Update() {
  return PressureSpectrumPointer(new PressureSpectrum(Size(10, 20)));
}