#ifndef SIGNAL_H
#define SIGNAL_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace ARD
{
  typedef unsigned short SignalLevel;
  typedef std::vector<SignalLevel> SignalContent;
  
  class Signal
  {
  public:
    Signal(SignalContent content) : content_(content), head_(0) {};
    SignalLevel Pop();

  private:
    SignalContent content_;
    long head_;
  };

  typedef boost::shared_ptr<Signal> SignalPointer;
}

#endif //SIGNAL_H
