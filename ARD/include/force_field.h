#ifndef FORCE_FIELD_H
#define FORCE_FIELD_H

#include <boost/shared_ptr.hpp>
#include "force_spectrum.h"
#include "dct_engine_factory.h"
#include <fftw_array.h>

namespace ARD {
  class ForceSpectrum;
  class ForceField
  {
  public:
    ForceField(const Size& size, const DCTEngineFactoryPointer engine_factory);
    ForceSpectrumPointer DCT();
    void set_content(const Position& position, const Precision_t& input) { engine->input()->set_content(position, input); };
    void FillBy(const Precision_t& input) { engine->input()->FillBy(input); };
    const Precision_t content(const Position& position) const { return engine->input()->content(position); };

  private:
    DCTEnginePointer engine;
  };

  typedef boost::shared_ptr<ForceField> ForceFieldPointer;
}

#endif // FORCE_FIELD_H
