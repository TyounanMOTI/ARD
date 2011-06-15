#include "output_fftw_array.h"

void PlotFFTWComplexArray(size_t size, fftw_complex* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (size_t i = 0; i < size; i++) {
    ofs << input[i][0] << std::endl;
  }
}

void PlotFFTWRealArray(size_t size, double* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (size_t i = 0; i < size; i++) {
    ofs << input[i] << std::endl;
  }
}

void OutputFFTWReal2DArray(int width, int height, double* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      ofs << input[row*width + col] << ' ';
    }
    ofs << std::endl;
  }
}
