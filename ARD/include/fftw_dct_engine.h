#include <boost/shared_ptr.hpp>
#include <fftw3.h>
#include "dct_engine.h"
#include "fftw_array.h"

namespace ARD
{
  class FFTWDCTEngine : public DCTEngine
  {
  public:
    enum TransformDirection {
      Forward = FFTW_REDFT10,
      Backward = FFTW_REDFT01,
    };

    FFTWDCTEngine(const Size& size, const TransformDirection direction);
    const FFTWArrayPointer input() const { return input_; }
    const FFTWArrayPointer Execute();

  private:
    void Normalize();

    fftw_plan plan_;
    FFTWArrayPointer input_;
    FFTWArrayPointer output_;
  };

  typedef boost::shared_ptr<FFTWDCTEngine> FFTWDCTEnginePointer;
}
