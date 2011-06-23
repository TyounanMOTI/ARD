#include <spectrum_pool.h>

using namespace ARD;

PressureFieldPointer SpectrumPool::Update() {
  return PressureFieldPointer(new PressureField(Size(10, 20)));
}