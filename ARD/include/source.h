#ifndef SOURCE_H
#define SOURCE_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <deque>
#include "power.h"
#include "position.h"

namespace ARD
{
  class Source
  {
  public:
    Source(const Position& position, std::vector<Power> content);
    Power Pop();
    const Position position() { return position_; };
    
  private:
    Position position_;
    std::deque<Power> content_;
  };
  
  typedef boost::shared_ptr<Source> SourcePointer;
}

#endif //SOURCE_H