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
  private:
    typedef boost::shared_ptr<ForceField<Precision> > ForceFieldPointer;

  public:
    Source(const Position& position, std::vector<Precision> content);
    const Precision Pop();
    void Emit(ForceFieldPointer force);
    const Position position() const { return position_; };
    
  private:
    Position position_;
    std::deque<Precision> content_;
  };
  
  template <class Precision>
  Source<Precision>::Source(const Position& position, std::vector<Precision> content) : position_(position) {
    content_.assign(content.begin(), content.end());
  }
  
  template <class Precision>
  const Precision Source<Precision>::Pop() {
    if (content_.empty()) {
      return Precision(0.0);
    }
    Precision result = content_.front();
    content_.pop_front();
    return result;
  }
  
  template <class Precision>
  void Source<Precision>::Emit(boost::shared_ptr<ForceField<Precision> > force) {
    force->set_content(position_, Pop());
  }
}

#endif //SOURCE_H
