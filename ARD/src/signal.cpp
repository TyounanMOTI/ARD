#include <signal.h>

using namespace ARD;

SignalLevel Signal::Pop() {
  SignalLevel output = content_[head_];
  head_++;
  return output;
}
