#include <fftw_dct_engine_factory.h>

using namespace ARD;

DCTEnginePointer FFTWDCTEngineFactory::GenerateForwardEngine(const Size& size) {
  return FFTWDCTEnginePointer(new FFTWDCTEngine(size, FFTWDCTEngine::Forward));
}

DCTEnginePointer FFTWDCTEngineFactory::GenerateBackwardEngine(const Size& size) {
  return FFTWDCTEnginePointer(new FFTWDCTEngine(size, FFTWDCTEngine::Backward));
}
