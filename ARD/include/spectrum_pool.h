#ifndef SPECTRUM_POOL_H
#define SPECTRUM_POOL_H

#include <boost/shared_ptr.hpp>
#include "position.h"
#include "point_microphone.h"
#include "pressure_field.h"

namespace ARD
{
  class SpectrumPool
  {
  public:
    PressureFieldPointer Update();
  };

  typedef boost::shared_ptr<SpectrumPool> SpectrumPoolPointer;
};

#endif // SPECTRUM_POOL_H