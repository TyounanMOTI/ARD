#include <gtest/gtest.h>
#include <fstream>
#include <fftw3.h>

void PlotFFTWComplexArray(size_t size, fftw_complex* input) {
  std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
  for (size_t i = 0; i < size; i++) {
    ofs << input[i][0] << std::endl;
  }
}

TEST(FFTWTest, initialization) {
  fftw_complex* subject = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * 100));
  subject[0][0] = 4.0;
  EXPECT_EQ(4.0, subject[0][0]);
  fftw_free(subject);
}

TEST(FFTWTest, DFT) {
  int size = 128;
  fftw_complex* input = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * size));
  fftw_complex* output = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * size));
  
  fftw_plan plan = fftw_plan_dft_1d(size, input, output, FFTW_FORWARD, FFTW_MEASURE);

  for (int i = 0; i < size; i++) {
    input[i][0] = 10.0;
  }
  fftw_execute(plan);
  
  EXPECT_EQ(size*10.0, output[0][0]);
  PlotFFTWComplexArray(size, output);
  
  fftw_free(input);
  fftw_free(output);
  fftw_destroy_plan(plan);
}