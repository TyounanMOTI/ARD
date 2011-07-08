#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include "pressure_field.h"

namespace ARD
{
  class Microphone
  {
  public:
    Microphone() {};
    virtual ~Microphone() {};
    virtual void Record(const PressureFieldPointer field) = 0;
  };

  typedef boost::shared_ptr<Microphone> MicrophonePointer;
}

#endif //MICROPHONE_H