#include <gtest/gtest.h>
#include <boost/multi_array.hpp>
#include <fftw_multi_array.h>

using namespace ARD;

TEST(FFTWFloat2DArrayTest, SetterAndGetter) {
  FFTWFloat2DArray subject(boost::extents[20][10]);
  subject[10][5] = 10.0f;
  EXPECT_FLOAT_EQ(10.0f, subject[10][5]);
}
