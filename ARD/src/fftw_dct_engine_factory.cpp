#include <fftw_dct_engine_factory.h>

using namespace ARD;

FFTWDCTEnginePointer FFTWDCTEngineFactory::GenerateEngine(const Size& size, const TransformDirection direction) {
  return FFTWDCTEnginePointer(new FFTWDCTEngine(size, direction));
}
