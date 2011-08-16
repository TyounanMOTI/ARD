#include <fftw_double_dct_engine_factory.h>

using namespace ARD;

boost::shared_ptr<DCTEngine<double> > FFTWDoubleDCTEngineFactory::GenerateForwardEngine(const Size& size) {
  return boost::shared_ptr<FFTWDoubleDCTEngine>(new FFTWDoubleDCTEngine(size, FFTWDoubleDCTEngine::Forward));
}

boost::shared_ptr<DCTEngine<double> > FFTWDoubleDCTEngineFactory::GenerateBackwardEngine(const Size& size) {
  return boost::shared_ptr<FFTWDoubleDCTEngine>(new FFTWDoubleDCTEngine(size, FFTWDoubleDCTEngine::Backward));
}
