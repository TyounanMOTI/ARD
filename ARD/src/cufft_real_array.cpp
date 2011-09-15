#include "cufft_real_array.h"

using namespace ARD;

CufftRealArray::CufftRealArray(const Size& size) : size_(size) {
  content_ = Allocate(size);
  ArrayInterface<float>::FillByZero();
}

CufftRealArray::ArrayContent CufftRealArray::Allocate(const Size& size) const {
  float* pHost;
  cudaHostAlloc(&pHost, sizeof(float)*size.Length(), cudaHostAllocMapped);
  return ArrayContent(pHost, cudaFreeHost);
}

CufftRealArray::ArrayInterfacePointer CufftRealArray::Clone() const {
  ArrayInterfacePointer cloned(new CufftRealArray(size_));
  cudaMemcpy(cloned->get(), content_.get(), sizeof(cufftReal)*size_.Length(), cudaMemcpyHostToHost);
  return cloned;
}
