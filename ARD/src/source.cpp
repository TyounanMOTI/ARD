#include "source.h"

using namespace ARD;

Source::Source(const Position& position, std::vector<Power> content) : position_(position) {
  content_.assign(content.begin(), content.end());
}

const Power Source::Pop() {
  if (content_.empty()) {
    return Power(0.0);
  }
  Power result = content_.front();
  content_.pop_front();
  return result;
}

void Source::Emit(ForceFieldPointer force) {
  force->content()->set_content(position_, Pop());
}
