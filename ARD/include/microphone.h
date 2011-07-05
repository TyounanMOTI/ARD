#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include <queue>
#include "position.h"
#include "signal.h"
#include "pressure.h"
#include "pressure_field.h"

namespace ARD
{
  typedef std::queue<Pressure> PressureQueue;
  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
  class Microphone
  {
  public:
    Microphone(const Position& position) : position_(position) {};
    const PressureQueue content() const;
    const Position position() const;
    void Push(const Pressure& input);
    void Pop(const int amount);
    void Record(const PressureFieldPointer field);

  private:
    Position position_;
    PressureQueue content_;
  };

  typedef boost::shared_ptr<Microphone> MicrophonePointer;
};

#endif // MICROPHONE_H
