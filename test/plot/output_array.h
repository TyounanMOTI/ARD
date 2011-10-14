#ifndef OUTPUT_ARRAY_H
#define OUTPUT_ARRAY_H

#include <fstream>
#include <cufft.h>

template <class C> void OutputRealPartOfComplexArray(int length, C* input);
template <> void OutputRealPartOfComplexArray(int length, cufftComplex* input);
template <class R> void OutputRealArray(int length, R* input);
template <class R> void OutputReal2DArray(int width, int height, R* input);
void OutputInterleavedComplexArray(int length, cufftComplex* input);

template <class C>
void OutputRealPartOfComplexArray(int length, C* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (size_t i = 0; i < length; i++) {
    ofs << input[i][0] << std::endl;
  }
}

template <class R>
void OutputRealArray(int length, R* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (size_t i = 0; i < length; i++) {
    ofs << input[i] << std::endl;
  }
}

template <class R>
void OutputReal2DArray(int width, int height, R* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      ofs << input[row*width + col] << ' ';
    }
    ofs << std::endl;
  }
}

#endif // OUTPUT_ARRAY_H
