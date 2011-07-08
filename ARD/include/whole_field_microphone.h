#ifndef WHOLE_FIELD_MICROPHONE_H
#define WHOLE_FIELD_MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include <queue>
#include "pressure_field.h"

namespace ARD {
  class WholeFieldMicrophone
  {
  public:
    WholeFieldMicrophone() {};
    const PressureFieldPointer Pop();
    void Record(const PressureFieldPointer field);

  private:
    std::queue<PressureFieldPointer> content_;
  };

  typedef boost::shared_ptr<WholeFieldMicrophone> WholeFieldMicrophonePointer;
}

#endif //WHOLE_FIELD_MICROPHONE_H