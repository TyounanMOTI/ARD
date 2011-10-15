#include <gtest/gtest.h>
#include <boost/shared_array.hpp>
#include <fftw3.h>

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

  fftw_destroy_plan(plan);
}

TEST(FFTWTest, DCT2D) {
  int width = 128;
  int height = 128;
  int length = width*height;
  boost::shared_array<double> input(static_cast<double*>(fftw_malloc(sizeof(double)*length)), fftw_free);
  boost::shared_array<double> output(static_cast<double*>(fftw_malloc(sizeof(double)*length)), fftw_free);
  
  fftw_plan plan = fftw_plan_r2r_2d(width, height, input.get(), output.get(), FFTW_REDFT10, FFTW_REDFT10, FFTW_MEASURE);
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      input[row*width + col] = 1.0;
    }
  }
  fftw_execute(plan);
  EXPECT_EQ(2*2*width*height*1.0, output[0]);
  EXPECT_EQ(0, output[100]);
  
  fftw_destroy_plan(plan);
}

TEST(FFTWTest, DCTI1D) {
  int length = 128;
  boost::shared_array<double> buffer(static_cast<double*>(fftw_malloc(sizeof(double)*length)), fftw_free);
  fftw_plan plan = fftw_plan_r2r_1d(length, buffer.get(), buffer.get(), FFTW_REDFT00, FFTW_ESTIMATE);
  for (int i = 0; i < length; i++) {
    buffer[i] = 1.0;
  }
  fftw_execute(plan);
  EXPECT_EQ(1.0, buffer[0]/(2.0*(length-1)));

  fftw_destroy_plan(plan);
}

TEST(FFTWTest, DCTI2D) {
  int width = 10;
  int height = 20;
  boost::shared_array<double> buffer(static_cast<double*>(fftw_malloc(sizeof(double)*width*height)), fftw_free);
  fftw_plan plan = fftw_plan_r2r_2d(height, width, buffer.get(), buffer.get(), FFTW_REDFT00, FFTW_REDFT00, FFTW_ESTIMATE);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      buffer[j + i * width] = 1.0;
    }
  }
  fftw_execute(plan);
  EXPECT_EQ(1.0, buffer[0]/(2.0*(width-1)*2.0*(height-1)));

  fftw_destroy_plan(plan);
}

TEST(FFTWTest, IDCT2DOnlyValueInHead) {
  int width = 128;
  int height = 128;
  int length = width*height;
  boost::shared_array<double> input(static_cast<double*>(fftw_malloc(sizeof(double)*length)), fftw_free);
  boost::shared_array<double> output(static_cast<double*>(fftw_malloc(sizeof(double)*length)), fftw_free);
  
  fftw_plan plan = fftw_plan_r2r_2d(width, height, input.get(), output.get(), FFTW_REDFT01, FFTW_REDFT01, FFTW_MEASURE);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      input[y*width + x] = 0.0;
    }
  }
  input[0] = 1.0;
  fftw_execute(plan);
  
  EXPECT_EQ(1.0, output[0]);
  EXPECT_EQ(1.0, output[100]);
  
  fftw_destroy_plan(plan);
}
