#ifdef CUDA
#include "output_array.h"

void OutputInterleavedComplexArray(int length, cufftComplex* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (size_t i = 0; i < length; i++) {
    ofs << input[i].x << std::endl << input[i].y << std::endl;
  }
}

template <>
void OutputRealPartOfComplexArray(int length, cufftComplex* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (size_t i = 0; i < length; i++) {
    ofs << input[i].x << std::endl;
  }
}

#endif

