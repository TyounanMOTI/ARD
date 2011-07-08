#include <fftw_array.h>

using namespace ARD;

FFTWArray::FFTWArray(const Size& size) : size_(size) {
  content_ = FFTWArrayContent(static_cast<Precision*>(fftw_malloc(sizeof(Precision)*size_.Length())),
                       fftw_free);
  FillByZero();
}

FFTWArray::FFTWArray(const FFTWArray& original) : size_(original.size_) {
  content_ = FFTWArrayContent(static_cast<Precision*>(fftw_malloc(sizeof(Precision)*original.size_.Length())),
                              fftw_free);
  memcpy(content_.get(), original.content_.get(), sizeof(Precision)*original.size_.Length());
}

Precision* FFTWArray::get() const {
  return content_.get();
}

const Size FFTWArray::size() const {
  return size_;
}

const Precision FFTWArray::content(const Position& position) const {
  return content_[FFTWArrayIndexFromPosition(position, size_)];
}

void FFTWArray::set_content(const Position& position, const Precision& input) {
  content_[FFTWArrayIndexFromPosition(position, size_)] = input;
}

void FFTWArray::FillByZero() {
  for (int y = 0; y < size().height(); y++) {
    for (int x = 0; x < size().width(); x++) {
      set_content(Position(x,y), Precision(0.0));
    }
  }
}

const size_t ARD::FFTWArrayIndexFromPosition(const Position& position, const Size& size) {
  return position.x() + position.y()*size.width();
}
