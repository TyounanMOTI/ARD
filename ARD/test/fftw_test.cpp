#include <gtest/gtest.h>
#include <fftw3.h>

TEST(FFTWTest, initialization) {
  fftw_complex* subject = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * 100));
  subject[0][0] = 4.0;
  EXPECT_EQ(subject[0][0], 4.0);
  fftw_free(subject);
}
