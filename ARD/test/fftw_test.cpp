#include <gtest/gtest.h>
#include <fstream>
#include <boost/shared_array.hpp>
#include <fftw3.h>

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
//  PlotFFTWComplexArray(size, output);
  
  fftw_destroy_plan(plan);
}

TEST(FFTWTest, DCT) {
  int size = 128;
  boost::shared_array<double> input(static_cast<double*>(fftw_malloc(sizeof(double)*size)), fftw_free);
  boost::shared_array<double> output(static_cast<double*>(fftw_malloc(sizeof(double)*size)), fftw_free);
 
  fftw_plan plan = fftw_plan_r2r_1d(size, input.get(), output.get(), FFTW_REDFT10, FFTW_MEASURE);
  for (int i = 0; i < size; i++) {
    input[i] = 10.0;
  }
  fftw_execute(plan);

  EXPECT_EQ(size*2*10.0, output[0]);
//  PlotFFTWRealArray(size, output.get());

  fftw_destroy_plan(plan);
}
