#ifndef FFTW_DCT_ENGINE_FACTORY_H
#define FFTW_DCT_ENGINE_FACTORY_H

#include <boost/shared_ptr.hpp>
#include "dct_engine.h"
#include "dct_engine_factory.h"
#include "fftw_double_dct_engine.h"
#include "fftw_float_dct_engine.h"

namespace ARD {
  template <class Precision>
  class FFTWDCTEngineFactory : public DCTEngineFactory<Precision>
  {
  private:
    typedef boost::shared_ptr<DCTEngine<Precision> > DCTEnginePointer;
    
  public:
    DCTEnginePointer GenerateForwardEngine(const Size& size);
    DCTEnginePointer GenerateBackwardEngine(const Size& size);
  };
  
  template <class Precision>
  typename FFTWDCTEngineFactory<Precision>::DCTEnginePointer FFTWDCTEngineFactory<Precision>::GenerateForwardEngine(const Size& size) {
    return DCTEnginePointer(new FFTWDoubleDCTEngine(size, FFTWDoubleDCTEngine::Forward));    
  }
  
  template <class Precision>
  typename FFTWDCTEngineFactory<Precision>::DCTEnginePointer FFTWDCTEngineFactory<Precision>::GenerateBackwardEngine(const Size& size) {
    return DCTEnginePointer(new FFTWDoubleDCTEngine(size, FFTWDoubleDCTEngine::Backward));    
  }
  
  template <>
  boost::shared_ptr<DCTEngine<float> > FFTWDCTEngineFactory<float>::GenerateForwardEngine(const Size& size);
  
  template <>
  boost::shared_ptr<DCTEngine<float> > FFTWDCTEngineFactory<float>::GenerateBackwardEngine(const Size& size);
}

#endif // FFTW_DCT_ENGINE_FACTORY_H
