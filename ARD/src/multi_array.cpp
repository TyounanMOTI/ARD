#include <multi_array.h>

using namespace ARD;

MultiArray::MultiArray(Size size) : size_(size) {
  content_ = FFTWComplexArray(static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex)*size_.Length())),
                              fftw_free);

}

Size MultiArray::size() {
  return size_;
}

Pressure MultiArray::content(Position position) {
  return content_[MultiArrayIndexFromPosition(position, size_)][0];
}

void MultiArray::set_content(Position position, double input) {
  content_[MultiArrayIndexFromPosition(position, size_)][0] = input;
}

const size_t ARD::MultiArrayIndexFromPosition(const Position& position, const Size& size) {
  return position.y() + position.x()*size.height();
}
