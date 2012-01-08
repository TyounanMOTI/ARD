#include <gtest/gtest.h>
#include <fftw_dct_engine.h>
#include <fftw_multi_array.h>

using namespace ARD;

TEST(FFTWDCTEngineTest, Initialize) {
  FFTWFloat2DArray data(boost::extents[10][20]);
  DCTEngine<FFTWFloat2DArray, Forward> engine(data);
}
