#include <gtest/gtest.h>
#include <fftw_dct_engine.h>
#include <fftw_multi_array.h>

using namespace ARD;

TEST(FFTWDCTEngineTest, Forward2DFloatDCT) {
  FFTWFloat2DArray data(boost::extents[10][20]);
  data.Fill(1);
  DCTEngine<FFTWFloat2DArray, Forward> engine(data);
  const FFTWFloat2DArray& output = engine.Execute();
  EXPECT_FLOAT_EQ(1, output[0][0]);
}

TEST(FFTWDCTEngineTest, Backward2DFloatDCT) {
  FFTWFloat2DArray data(boost::extents[10][20]);
  DCTEngine<FFTWFloat2DArray, Backward> engine(data, data);
  data[0][0] = 1;
  const FFTWFloat2DArray& output = engine.Execute();
  EXPECT_FLOAT_EQ(1, output[0][0]);
  EXPECT_FLOAT_EQ(1, output[9][19]);
}
