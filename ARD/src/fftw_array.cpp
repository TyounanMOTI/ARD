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

ArrayInterfacePointer FFTWArray::Clone() const {
  return FFTWArrayPointer(new FFTWArray(*this));
}

