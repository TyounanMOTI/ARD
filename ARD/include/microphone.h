#ifndef MICROPHONE_H
#define MICROPHONE_H

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
}

#endif //MICROPHONE_H