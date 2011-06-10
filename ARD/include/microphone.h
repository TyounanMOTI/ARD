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
    Microphone(const Position position) : position_(position) {};
    PressureQueue Content();
    void Push(const Pressure input);
    void Pop(const int amount);

  private:
    Position position_;
    PressureQueue content_;
  };

  typedef boost::shared_ptr<Microphone> MicrophonePointer;
};

#endif // MICROPHONE_H
