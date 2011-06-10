#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

namespace ARD
{
  class Signal
  {
  public:
    explicit Signal() : length(0) {};
    explicit Signal(std::vector<short> content) : content(content) {};
    std::vector<short> Content();
    const short at(const unsigned long pos);

    int length;

  private:
    std::vector<short> content;
  };
}

#endif
