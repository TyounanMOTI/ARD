#include <multi_array.h>

using namespace ARD;

MultiArray::MultiArray(const Size& size) : size_(size) {
  content_ = MultiArrayContent(static_cast<double*>(fftw_malloc(sizeof(double)*size_.Length())),
                       fftw_free);
}

Precision* MultiArray::get() const {
  return content_.get();
}

const Size MultiArray::size() const {
  return size_;
}

const Precision MultiArray::content(const Position& position) const {
  return content_[MultiArrayIndexFromPosition(position, size_)];
}

void MultiArray::set_content(const Position& position, const Precision& input) {
  content_[MultiArrayIndexFromPosition(position, size_)] = input;
}

const size_t ARD::MultiArrayIndexFromPosition(const Position& position, const Size& size) {
  return position.y() + position.x()*size.height();
}
