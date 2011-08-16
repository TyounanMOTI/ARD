#include <fftw_array.h>

using namespace ARD;

FFTWArray::FFTWArray(const Size& size) : size_(size) {
  content_ = FFTWArrayContent(static_cast<double*>(fftw_malloc(sizeof(double)*size_.Length())),
                              fftw_free);
  FillByZero();
}

FFTWArray::FFTWArray(const FFTWArray& original) : size_(original.size_) {
  content_ = FFTWArrayContent(static_cast<double*>(fftw_malloc(sizeof(double)*original.size_.Length())),
                              fftw_free);
  memcpy(content_.get(), original.content_.get(), sizeof(double)*original.size_.Length());
}

boost::shared_ptr<ArrayInterface<double> > FFTWArray::Clone() const {
  return FFTWArrayPointer(new FFTWArray(*this));
}

