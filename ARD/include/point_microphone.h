#ifndef POINT_MICROPHONE_H
#define POINT_MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include <queue>
#include "position.h"
#include "signal.h"
#include "pressure.h"
#include "pressure_field.h"
#include "microphone.h"

namespace ARD
{
  typedef std::queue<Pressure> PressureQueue;
  typedef boost::shared_ptr<PressureField> PressureFieldPointer;
  class PointMicrophone : public Microphone
  {
  public:
    PointMicrophone() : position_(Position(0,0)) {};
    PointMicrophone(const Position& position) : position_(position) {};
    const PressureQueue content() const;
    const Position position() const;
    const Pressure Pop();
    void Record(const PressureFieldPointer field);
    void Plot(PressureFieldPointer field);

  private:
    Position position_;
    PressureQueue content_;
  };

  typedef boost::shared_ptr<PointMicrophone> PointMicrophonePointer;
}

#endif // POINT_MICROPHONE_H
