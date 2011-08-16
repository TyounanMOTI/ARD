#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include "pressure_field.h"

namespace ARD
{
  template <class Precision>
  class Microphone
  {
  private:
    typedef boost::shared_ptr<PressureField<Precision> > PressureFieldPointer;
  public:
    Microphone() {};
    virtual ~Microphone() {};
    virtual const Precision Pop() = 0;
    virtual void Record(const PressureFieldPointer field) = 0;
    virtual void Plot(PressureFieldPointer field) = 0;
  };
}

#endif //MICROPHONE_H
