#include <fftw_array.h>

using namespace ARD;

template <>
FFTWArray<double>::FFTWArrayContent FFTWArray<double>::Allocate(const Size& size) {
  return FFTWArrayContent(static_cast<double*>(fftw_malloc(sizeof(double)*size.Length())),
                          fftw_free);
}
