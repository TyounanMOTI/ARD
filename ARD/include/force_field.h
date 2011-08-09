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
    ForceSpectrumPointer DCT();
    void set_content(const Position& position, const Precision& input) { engine->input()->set_content(position, input); };
    void FillBy(const Precision& input) { engine->input()->FillBy(input); };
    const Precision content(const Position& position) const { return engine->input()->content(position); };

  private:
    DCTEnginePointer engine;
  };

  typedef boost::shared_ptr<ForceField> ForceFieldPointer;
};

#endif // FORCE_FIELD_H
