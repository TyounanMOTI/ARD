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
    std::vector<short> Content();
    const short at(const unsigned long pos);

    int length_;

  private:
    std::vector<short> content_;
  };
}

#endif
