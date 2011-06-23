#include <signal.h>

using namespace ARD;

std::vector<short> Signal::content() const {
  return content_;
}

short Signal::at(const unsigned long pos) const {
  return content_.at(pos);
}

int Signal::size() const {
  return content_.size();
}
