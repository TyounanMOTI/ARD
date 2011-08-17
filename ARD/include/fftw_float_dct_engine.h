#ifndef FFTW_FLOAT_DCT_ENGINE_H
#define FFTW_FLOAT_DCT_ENGINE_H

#include <boost/shared_ptr.hpp>
#include <fftw3.h>
#include "dct_engine.h"
#include "fftw_array.h"

namespace ARD
{
  typedef boost::shared_ptr<fftwf_plan_s> FFTWFloatPlan;  
  
  class FFTWFloatDCTEngine : public DCTEngine<float>
  {
  private:
    typedef boost::shared_ptr<ArrayInterface<float> > ArrayInterfacePointer;
    typedef boost::shared_ptr<FFTWArray<float> > FFTWArrayPointer;
    
  public:
    enum TransformDirection {
      Forward = FFTW_REDFT10,
      Backward = FFTW_REDFT01,
    };
    
    FFTWFloatDCTEngine(const Size& size, const TransformDirection direction);
    const ArrayInterfacePointer input() const { return input_; }
    const ArrayInterfacePointer Execute();
    
  private:
    void Normalize();
    
    FFTWFloatPlan plan_;
    FFTWArrayPointer input_;
    FFTWArrayPointer output_;
    TransformDirection direction_;
  };
  
  typedef boost::shared_ptr<FFTWFloatDCTEngine> FFTWFloatDCTEnginePointer;
}

#endif // FFTW_DCT_ENGINE_H