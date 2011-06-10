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
  return content[position.Y() + position.X()*size_.Height()][0];
}

void MultiArray::SetContent(Position position, double input) {
  content[position.Y() + position.X()*size_.Height()][0] = input;
}
