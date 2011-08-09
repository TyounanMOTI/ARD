#ifndef FORCE_FIELD_H
#define FORCE_FIELD_H

#include <boost/shared_ptr.hpp>
#include "force_spectrum.h"
#include "dct_engine_factory.h"
#include "fftw_plan.h"
#include <fftw_array.h>

namespace ARD {
  class ForceSpectrum;
  class ForceField
  {
  public:
    ForceField(const Size& size, const DCTEngineFactoryPointer engine_factory);
    FFTWArrayPointer content() { return engine->input(); };
    ForceSpectrumPointer DCT();

  private:
    DCTEnginePointer engine;
  };

  typedef boost::shared_ptr<ForceField> ForceFieldPointer;
};

#endif // FORCE_FIELD_H
