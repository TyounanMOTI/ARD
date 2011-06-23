#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

namespace ARD
{
  typedef std::vector<short> SignalContent;

  class Signal
  {
  public:
    explicit Signal() {};
    explicit Signal(SignalContent content) : content_(content) {};
    std::vector<short> content() const;
    short at(const unsigned long pos) const;
    int size() const;
    
  private:
    SignalContent content_;
  };
}

#endif
