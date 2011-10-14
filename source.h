#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include <deque>
#include "position.h"
#include "force_field.h"

namespace ARD
{
  template <class Precision>
  class Source
  {
  public:
    typedef std::deque<Precision> Content;

    Source(const Position& position, Content content);
    const Precision Pop();
    template <class ForceField> void Emit(ForceField& forceField);
    const Position position() const { return position_; };
    
  private:
    Position position_;
    Content content_;
  };
  
  template <class Precision>
  Source<Precision>::Source(const Position& position, Content content) : position_(position), content_(content) {};
  
  template <class Precision>
  const Precision Source<Precision>::Pop() {
    if (content_.empty()) {
      return Precision(0.0);
    }
    Precision result = content_.front();
    content_.pop_front();
    return result;
  }
  
  template <class Precision> template <class ForceField>
  void Source<Precision>::Emit(ForceField& forceField) {
    forceField(position_) = Pop();
  }
}

