#ifndef FORCE_FIELD_H
#define FORCE_FIELD_H

#include <boost/shared_ptr.hpp>
#include "force_spectrum.h"
#include "dct_engine_factory.h"
#include <fftw_array.h>

namespace ARD {
  template<class Precision> class ForceSpectrum;
  
  template<class Precision>
  class ForceField
  {
  private:
    typedef boost::shared_ptr<DCTEngineFactory<Precision> > DCTEngineFactoryPointer;
    typedef boost::shared_ptr<ForceSpectrum<Precision> > ForceSpectrumPointer;
  public:
    ForceField(const Size& size, const DCTEngineFactoryPointer engine_factory);
    ForceSpectrumPointer DCT();
    void set_content(const Position& position, const Precision& input) { engine->input()->set_content(position, input); };
    void FillBy(const Precision& input) { engine->input()->FillBy(input); };
    const Precision content(const Position& position) const { return engine->input()->content(position); };

  private:
    boost::shared_ptr<DCTEngine<Precision> > engine;
  };
  
  template <class Precision>
  ForceField<Precision>::ForceField(const Size& size, const boost::shared_ptr<DCTEngineFactory<Precision> > engine_factory) {
    engine = engine_factory->GenerateForwardEngine(size);
  }
  
  template <class Precision>
  boost::shared_ptr<ForceSpectrum<Precision> > ForceField<Precision>::DCT() {
    return boost::shared_ptr<ForceSpectrum<Precision> >(new ForceSpectrum<Precision>(engine->Execute()));
  }
}

#endif // FORCE_FIELD_H
