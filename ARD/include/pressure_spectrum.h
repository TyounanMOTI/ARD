#ifndef PRESSURE_SPECTRUM_H
#define PRESSURE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include "fftw_array.h"
#include "pressure_field.h"
#include "size.h"
#include "dct_engine.h"
#include "dct_engine_factory.h"
#include <fftw3.h>

namespace ARD
{
  class PressureField;
  typedef boost::shared_ptr<PressureField> PressureFieldPointer;

  class PressureSpectrum
  {
  public:
    PressureSpectrum(const Size& size, const DCTEngineFactoryPointer engine_factory);
    PressureFieldPointer InverseDCT();
    const Size size() { return engine->input()->size(); };
    const Precision content(const Position& position) { return engine->input()->content(position); };
    void set_content(const Position& position, const Precision input) { engine->input()->set_content(position, input); };

  private:
    DCTEnginePointer engine;
  };  

  typedef boost::shared_ptr<PressureSpectrum> PressureSpectrumPointer;
}

#endif // PRESSURE_SPECTRUM_H
