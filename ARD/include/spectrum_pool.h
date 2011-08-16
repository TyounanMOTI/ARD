#ifndef SPECTRUM_POOL_H
#define SPECTRUM_POOL_H

#include <boost/shared_ptr.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "position.h"
#include "pressure_spectrum.h"
#include "force_spectrum.h"
#include "dct_engine_factory.h"

namespace ARD
{
  template <class Precision>
  class SpectrumPool
  {
  private:
    typedef boost::shared_ptr<DCTEngineFactory<Precision> > DCTEngineFactoryPointer;
    typedef boost::shared_ptr<PressureSpectrum<Precision> > PressureSpectrumPointer;
    typedef boost::shared_ptr<ForceSpectrum<Precision> > ForceSpectrumPointer;
    
  public:
    SpectrumPool(const Size& size, const Precision dt, const DCTEngineFactoryPointer engine_factory);
    PressureSpectrumPointer Update(const ForceSpectrumPointer force_spectrum);

  private:
    void TimeShift();

    PressureSpectrumPointer previous_, now_, next_;
    Precision dt_;
    static const Precision c;
  };
  
  template <class Precision>
  const Precision SpectrumPool<Precision>::c = 340.0;
  
  template <class Precision>
  SpectrumPool<Precision>::SpectrumPool(const Size& size, const Precision dt, const boost::shared_ptr<DCTEngineFactory<Precision> > engine_factory) : dt_(dt) {
    previous_.reset(new PressureSpectrum<Precision>(size, engine_factory));
    now_.reset(new PressureSpectrum<Precision>(size, engine_factory));
    next_.reset(new PressureSpectrum<Precision>(size, engine_factory));
  }
  
  template <class Precision>
  boost::shared_ptr<PressureSpectrum<Precision> > SpectrumPool<Precision>::Update(const boost::shared_ptr<ForceSpectrum<Precision> > force_spectrum) {
    Size size = force_spectrum->size();
    Position position;
    double omega = 0.0;
    for (long y = 0; y < size.height(); y++) {
      for (long x = 0; x < size.width(); x++) {
        omega = c * M_PI * sqrt((double)x*x/(size.width()*size.width()-1) + (double)y*y/(size.height()*size.height()-1));
        position = Position(x,y);
        next_->set_content(position,
                           Precision(2.0*now_->content(position)*cos(omega*dt_) - previous_->content(position)
                                           + 2.0*force_spectrum->content(position)/(omega*omega)*(1-cos(omega*dt_))));
      }
    }
    next_->set_content(Position(0,0), Precision(0.0)); // next_[0,0] is divided by zero
    boost::shared_ptr<PressureSpectrum<Precision> > result = next_;
    TimeShift();
    return next_;
  }
  
  template <class Precision>
  void SpectrumPool<Precision>::TimeShift() {
    boost::shared_ptr<PressureSpectrum<Precision> > temp = previous_;
    previous_ = now_;
    now_ = next_;
    next_ = temp;
  }
}

#endif // SPECTRUM_POOL_H
