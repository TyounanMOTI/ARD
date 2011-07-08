#ifndef WHOLE_FIELD_MICROPHONE_H
#define WHOLE_FIELD_MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include <queue>
#include "pressure_field.h"
#include "microphone.h"

namespace ARD {
  class WholeFieldMicrophone : public Microphone
  {
  public:
    WholeFieldMicrophone() {};
    const Pressure Pop();
    void Record(const PressureFieldPointer field);
    void Plot(PressureFieldPointer field);

  private:
    std::queue<PressureFieldPointer> content_;
  };

  typedef boost::shared_ptr<WholeFieldMicrophone> WholeFieldMicrophonePointer;
}

#endif //WHOLE_FIELD_MICROPHONE_H