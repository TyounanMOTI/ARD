#ifndef SPECTRUM_POOL_H
#define SPECTRUM_POOL_H

#include <boost/shared_ptr.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "position.h"
#include "point_microphone.h"
#include "pressure_spectrum.h"
#include "force_spectrum.h"
#include "mode_coefficient.h"

namespace ARD
{
  class SpectrumPool
  {
  public:
    SpectrumPool(const Size& size, const double dt);
    PressureSpectrumPointer Update(const ForceSpectrumPointer force_spectrum);

  private:
    void TimeShift();

    PressureSpectrumPointer previous_, now_, next_;
    double dt_;
    static const double c;
  };

  typedef boost::shared_ptr<SpectrumPool> SpectrumPoolPointer;
}

#endif // SPECTRUM_POOL_H
