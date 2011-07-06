#include "source.h"

using namespace ARD;

Source::Source(const Position& position, std::vector<Power> content) : position_(position) {
  content_.assign(content.begin(), content.end());
}

Power Source::Pop() {
  Power result = content_.front();
  content_.pop_front();
  return result;
}
