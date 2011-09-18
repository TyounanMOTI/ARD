#include <cufft_dct_forward_engine.h>

using namespace ARD;

CufftDCTForwardEngine::CufftDCTForwardEngine(const Size& size) {
  input_.reset(new CufftRealArray(size));
}
