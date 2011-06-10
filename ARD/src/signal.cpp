#include <signal.h>

using namespace ARD;

std::vector<short> Signal::Content() {
  return content_;
}

const short Signal::at(const unsigned long pos) {
  return content_.at(pos);
}
