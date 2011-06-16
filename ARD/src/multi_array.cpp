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

MultiArrayContent MultiArray::content() const {
  return content_;
}

const Precision MultiArray::content(const Position& position) const {
  return content_[MultiArrayIndexFromPosition(position, size_)];
}

void MultiArray::set_content(const Position& position, const Precision& input) {
  content_[MultiArrayIndexFromPosition(position, size_)] = input;
}

void MultiArray::FillByZero() {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), Precision(0.0));
    }
  }
}

const size_t ARD::MultiArrayIndexFromPosition(const Position& position, const Size& size) {
  return position.x() + position.y()*size.width();
}
