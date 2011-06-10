#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

namespace ARD
{
  class Signal
  {
  public:
    explicit Signal() : length_(0) {};
    explicit Signal(std::vector<short> content) : content_(content) {};
    std::vector<short> content();
    const short at(const unsigned long pos);
    const int length();
    
  private:
    int length_;
    std::vector<short> content_;
  };
}

#endif
