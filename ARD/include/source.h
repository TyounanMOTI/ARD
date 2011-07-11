#ifndef SOURCE_H
#define SOURCE_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <deque>
#include "power.h"
#include "position.h"
#include "force_field.h"

namespace ARD
{
  class Source
  {
  public:
    Source(const Position& position, std::vector<Power> content);
    const Power Pop();
    void Emit(ForceFieldPointer force);
    const Position position() const { return position_; };
    
  private:

    Position position_;
    std::deque<Power> content_;
  };
  
  typedef boost::shared_ptr<Source> SourcePointer;
}

#endif //SOURCE_H