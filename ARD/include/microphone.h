#ifndef MICROPHONE_H
#define MICROPHONE_H

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
};

#endif // MICROPHONE_H