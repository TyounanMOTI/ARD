#include <gtest/gtest.h>
#include <boost/multi_array.hpp>
#include <fftw_multi_array.h>

using namespace ARD;

class FFTWFloat2DArrayTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject.resize(boost::extents[20][10]);
  }

  FFTWFloat2DArray subject;
};

TEST_F(FFTWFloat2DArrayTest, SetterAndGetter) {
  subject[10][5] = 10.0f;
  EXPECT_FLOAT_EQ(10.0f, subject[10][5]);
}
