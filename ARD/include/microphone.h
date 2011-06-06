#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include "position.h"

namespace ARD
{
  class Microphone
  {
  public:
    Microphone(const Position position) : position(position) {};

  private:
    Position position;
  };

  typedef boost::shared_ptr<Microphone> MicrophonePointer;
};

#endif // MICROPHONE_H