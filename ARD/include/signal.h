#ifndef SIGNAL_H
#define SIGNAL_H

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

namespace ARD
{
  typedef unsigned short SignalLevel;
  typedef boost::shared_array<SignalLevel> SignalContent;
  
  class Signal
  {
  public:
    Signal(SignalContent content, long length);
    SignalLevel Pop();

  private:
    SignalContent content_;
    long length_;
    long head_;
  };

  typedef boost::shared_ptr<Signal> SignalPointer;
};

#endif //SIGNAL_H