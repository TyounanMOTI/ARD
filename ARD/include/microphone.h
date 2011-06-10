#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include <queue>
#include "position.h"
#include "signal.h"

namespace ARD
{
  typedef double Pressure;
  typedef std::queue<Pressure> PressureQueue;

  class Microphone
  {
  public:
    Microphone(const Position position) : position(position) {};
    PressureQueue Content();
    void Push(const Pressure input);

  private:
    Position position;
    PressureQueue content;
  };

  typedef boost::shared_ptr<Microphone> MicrophonePointer;
};

#endif // MICROPHONE_H