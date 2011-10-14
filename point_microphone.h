#ifndef POINT_MICROPHONE_H
#define POINT_MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include <queue>
#include "position.h"
#include "pressure_field.h"
#include "microphone.h"

namespace ARD
{
  template <class Precision>
  class PointMicrophone : public Microphone<Precision>
  {
  private:
    typedef boost::shared_ptr<PressureField<Precision> > PressureFieldPointer;
    typedef std::queue<Precision> ContentQueue;
    
  public:
    PointMicrophone() : position_(Position(0,0)) {};
    explicit PointMicrophone(const Position& position) : position_(position) {};
    const ContentQueue content() const;
    const Position position() const;
    const Precision Pop();
    void Record(const PressureFieldPointer field);
    void Plot(PressureFieldPointer field);

  private:
    Position position_;
    ContentQueue content_;
  };
  
  template <class Precision>
  const std::queue<Precision> PointMicrophone<Precision>::content() const {
    return content_;
  }
  
  template <class Precision>
  const Position PointMicrophone<Precision>::position() const {
    return position_;
  }
  
  template <class Precision>
  const Precision PointMicrophone<Precision>::Pop() {
    if (content_.empty()) {
      return Precision(0);
    }
    Precision result = content_.front();
    content_.pop();
    return result;
  }
  
  template <class Precision>
  void PointMicrophone<Precision>::Record(const boost::shared_ptr<PressureField<Precision> > field) {
    content_.push(field->content(position()));
  }
  
  template <class Precision>
  void PointMicrophone<Precision>::Plot(boost::shared_ptr<PressureField<Precision> > field) {
    field->set_content(position_, Pop());
  }
}

#endif // POINT_MICROPHONE_H
