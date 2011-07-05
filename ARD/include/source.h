#include <boost/shared_ptr.hpp>
#include <vector>
#include <deque>
#include "power.h"

namespace ARD
{
  class Source
  {
  public:
    Source(std::vector<Power> content);
    Power Pop();
    
  private:
    std::deque<Power> content_;
  };
  
  typedef boost::shared_ptr<Source> SourcePointer;
}