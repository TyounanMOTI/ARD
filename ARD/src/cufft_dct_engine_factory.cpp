#include <cufft_dct_engine_factory.h>

using namespace ARD;

CufftDCTEngineFactory::DCTEnginePointer CufftDCTEngineFactory::GenerateForwardEngine(const Size& size) {
  return DCTEnginePointer(new CufftDCTForwardEngine(size));
}

CufftDCTEngineFactory::DCTEnginePointer CufftDCTEngineFactory::GenerateBackwardEngine(const Size& size) {
  return DCTEnginePointer(new CufftDCTForwardEngine(size));
}
