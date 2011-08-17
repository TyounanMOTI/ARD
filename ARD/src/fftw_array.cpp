#include <fftw_array.h>

using namespace ARD;

FFTWArray::FFTWArray(const Size& size) : size_(size) {
  content_ = Allocate(size);
  FillByZero();
}

FFTWArray::FFTWArray(const FFTWArray& original) : size_(original.size_) {
  content_ = Allocate(original.size_);
  memcpy(content_.get(), original.content_.get(), sizeof(double)*original.size_.Length());
}

boost::shared_ptr<ArrayInterface<double> > FFTWArray::Clone() const {
  return FFTWArrayPointer(new FFTWArray(*this));
}

FFTWArray::FFTWArrayContent FFTWArray::Allocate(const Size& size) {
  return FFTWArrayContent(static_cast<double*>(fftw_malloc(sizeof(double)*size.Length())),
                          fftw_free);
}
