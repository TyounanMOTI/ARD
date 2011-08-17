#include <gtest/gtest.h>
#include <fftw_float_dct_engine.h>
#include <fftw_array.h>

using namespace ARD;

TEST(FFTWFloatDCTEngineTest, DCTDirectCurrent) {
  boost::shared_ptr<DCTEngine<float> > subject(new FFTWFloatDCTEngine(Size(10,20), FFTWFloatDCTEngine::Forward));
  subject->input()->FillBy(1.0);
  boost::shared_ptr<ArrayInterface<float> > output(subject->Execute());
  EXPECT_EQ(1.0, output->content(Position(0,0)));
}
