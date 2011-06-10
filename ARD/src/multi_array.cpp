#include <multi_array.h>

using namespace ARD;

MultiArray::MultiArray(Size size) : size_(size) {
  content = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex)*size_.Length()));

}

MultiArray::~MultiArray() {
  fftw_free(content);
}

Size MultiArray::GetSize() {
  return size_;
}

Pressure MultiArray::Content(Position position) {
  return content[MultiArrayIndexFromPosition(position, size_)][0];
}

void MultiArray::SetContent(Position position, double input) {
  content[MultiArrayIndexFromPosition(position, size_)][0] = input;
}

const size_t ARD::MultiArrayIndexFromPosition(Position position, Size size) {
  return position.Y() + position.X()*size.Height();
}
