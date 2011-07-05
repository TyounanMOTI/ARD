#include "source.h"

using namespace ARD;

Source::Source(std::vector<Power> content) {
  std::copy(content.begin(), content.end(), content_.begin());
}

Power Source::Pop() {
  Power result = content_.front();
  content_.pop_front();
  return result;
}
