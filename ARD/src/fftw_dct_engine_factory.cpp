#include <fftw_dct_engine_factory.h>

using namespace ARD;

template <>
boost::shared_ptr<DCTEngine<float> > FFTWDCTEngineFactory<float>::GenerateForwardEngine(const Size& size) {
  return boost::shared_ptr<FFTWFloatDCTEngine>(new FFTWFloatDCTEngine(size, FFTWFloatDCTEngine::Forward));
}

template <>
boost::shared_ptr<DCTEngine<float> > FFTWDCTEngineFactory<float>::GenerateBackwardEngine(const Size& size) {
  return boost::shared_ptr<FFTWFloatDCTEngine>(new FFTWFloatDCTEngine(size, FFTWFloatDCTEngine::Backward));
}
