#ifndef PRESSURE_SPECTRUM_H
#define PRESSURE_SPECTRUM_H

#include <boost/shared_ptr.hpp>
#include "size.h"
#include "dct_engine.h"
#include "dct_engine_factory.h"

namespace ARD
{
  template <class Precision> class PressureField;

  template <class Precision>
  class PressureSpectrum
  {
  private:
    typedef boost::shared_ptr<DCTEngineFactory<Precision> > DCTEngineFactoryPointer;
    typedef boost::shared_ptr<DCTEngine<Precision> > DCTEnginePointer;
    typedef boost::shared_ptr<PressureField<Precision> > PressureFieldPointer;
  public:
    PressureSpectrum(const Size& size, const DCTEngineFactoryPointer engine_factory);
    PressureFieldPointer InverseDCT();
    const Size size() const { return engine->input()->size(); };
    const Precision content(const Position& position) const { return engine->input()->content(position); };
    void set_content(const Position& position, const Precision& input) { engine->input()->set_content(position, input); };

  private:
    DCTEnginePointer engine;
  };
  
  template <class Precision>
  PressureSpectrum<Precision>::PressureSpectrum(const Size& size, const boost::shared_ptr<DCTEngineFactory<Precision> > engine_factory) {
    engine = engine_factory->GenerateBackwardEngine(size);
  }
  
  template <class Precision>
  boost::shared_ptr<PressureField<Precision> > PressureSpectrum<Precision>::InverseDCT() {
    return boost::shared_ptr<PressureField<Precision> >(new PressureField<Precision>(engine->Execute()));
  }
}

#endif // PRESSURE_SPECTRUM_H
