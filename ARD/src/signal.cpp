#include <signal.h>

using namespace ARD;

SignalContent Signal::content() const {
  return content_;
}

short Signal::at(const unsigned long pos) const {
  return content_.at(pos);
}

size_t Signal::size() const {
  return content_.size();
}
