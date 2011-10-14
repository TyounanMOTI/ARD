#ifndef WHOLE_FIELD_MICROPHONE_H
#define WHOLE_FIELD_MICROPHONE_H

#include <boost/shared_ptr.hpp>
#include <queue>
#include "pressure_field.h"
#include "microphone.h"

namespace ARD {
  template <class Precision>
  class WholeFieldMicrophone : public Microphone<Precision>
  {
  private:
    typedef boost::shared_ptr<PressureField<Precision> > PressureFieldPointer;
    
  public:
    WholeFieldMicrophone() {};
    const Precision Pop();
    void Record(const PressureFieldPointer field);
    void Plot(PressureFieldPointer field);

  private:
    std::queue<PressureFieldPointer> content_;
  };

  template <class Precision>
  const Precision WholeFieldMicrophone<Precision>::Pop() {
    if (!content_.empty()) {
      content_.pop();
    }
    return Precision(0.0);
  }
  
  template <class Precision>
  void WholeFieldMicrophone<Precision>::Record(const boost::shared_ptr<PressureField<Precision> > field) {
    content_.push(boost::shared_ptr<PressureField<Precision> >(new PressureField<Precision>(*field)));
  }
  
  template <class Precision>
  void WholeFieldMicrophone<Precision>::Plot(boost::shared_ptr<PressureField<Precision> > field) {
    if (content_.empty()) {
      return;
    }
    boost::shared_ptr<PressureField<Precision> > front = content_.front();
    Size size = field->size();
    for (int y = 0; y < size.height(); y++) {
      for (int x = 0; x < size.width(); x++) {
        field->set_content(Position(x,y), front->content(Position(x,y)));
      }
    }
    Pop();
  }
}

#endif //WHOLE_FIELD_MICROPHONE_H
