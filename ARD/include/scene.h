#pragma once

#include <boost/shared_ptr.hpp>
#include "size.h"
#include "microphone.h"
#include "source.h"
#include "force_field.h"
#include "spectrum_pool.h"
#include "dct_engine_factory.h"

namespace ARD
{
  template <class Precision>
  class Scene
  {
  private:
    typedef boost::shared_ptr<Microphone<Precision> > MicrophonePointer;
    typedef boost::shared_ptr<Source<Precision> > SourcePointer;
    typedef boost::shared_ptr<ForceField<Precision> > ForceFieldPointer;
    typedef boost::shared_ptr<SpectrumPool<Precision> > SpectrumPoolPointer;
    typedef boost::shared_ptr<DCTEngineFactory<Precision> > DCTEngineFactoryPointer;
    
  public:
    Scene(const Size& size, const Precision& dt, const DCTEngineFactoryPointer engine_factory);
    MicrophonePointer Update();
    Size size() { return size_; };
    void set_microphone(MicrophonePointer microphone) { microphone_ = microphone; };
    void set_source(SourcePointer source) { source_ = source; };

  private:
    Size size_;
    MicrophonePointer microphone_;
    SourcePointer source_;
    ForceFieldPointer force_field_;
    SpectrumPoolPointer spectrum_pool_;
  };
  
  template <class Precision>
  Scene<Precision>::Scene(const Size& size, const Precision& dt, const DCTEngineFactoryPointer engine_factory) : size_(size) {
    force_field_.reset(new ForceField<Precision>(size, engine_factory));
    spectrum_pool_.reset(new SpectrumPool<Precision>(size, dt, engine_factory));
  }
  
  template <class Precision>
  boost::shared_ptr<Microphone<Precision> > Scene<Precision>::Update() {
    force_field_->FillBy(Precision(0));
    source_->Emit(force_field_);
    boost::shared_ptr<PressureSpectrum<Precision> > pressure_spectrum(spectrum_pool_->Update(force_field_->DCT()));
    boost::shared_ptr<PressureField<Precision> > pressure_field(pressure_spectrum->InverseDCT());
    microphone_->Record(pressure_field);
    return microphone_;
  }
}
