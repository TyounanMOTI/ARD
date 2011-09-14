#include "cufft_real_array.h"

using namespace ARD;

CufftRealArray::CufftRealArray(const Size& size) {
  content_ = Allocate(size);
  ArrayInterface<float>::FillByZero();
}

CufftRealArray::ArrayContent CufftRealArray::Allocate(const Size& size) const {
  float* pHost;
  cudaHostAlloc(&pHost, sizeof(float)*size.Length(), cudaHostAllocDefault);
  return ArrayContent(pHost, cudaFreeHost);
}

CufftRealArray::ArrayInterfacePointer CufftRealArray::Clone() const {
  return ArrayInterfacePointer(new CufftRealArray(size_));
}
