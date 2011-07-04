#include <signal.h>

using namespace ARD;

Signal::Signal(SignalContent content, long length) : length_(length), head_(0) {
  content_ = SignalContent(new SignalLevel[length]);
  memmove(content_.get(), content.get(), sizeof(SignalLevel)*length);
}

SignalLevel Signal::Pop() {
  SignalLevel output = content_[head_];
  head_++;
  return output;
}
