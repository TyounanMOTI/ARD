#include <gtest/gtest.h>
#include <fftw_dct_engine.h>
#include <fftw_array.h>

using namespace ARD;

TEST(FFTWDoubleDCTEngineTest, DCTDirectCurrent) {
  boost::shared_ptr<DCTEngine<double> > subject(new FFTWDCTEngine<double, FFTWDoublePlan>(Size(10,20), FFTWDCTEngine<double, FFTWDoublePlan>::Forward));
  subject->input()->FillBy(1.0);
  boost::shared_ptr<ArrayInterface<double> > output(subject->Execute());
  EXPECT_EQ(1.0, output->content(Position(0,0)));
}

TEST(FFTWFloatDCTEngineTest, DCTDirectCurrent) {
  boost::shared_ptr<DCTEngine<float> > subject(new FFTWDCTEngine<float, FFTWFloatPlan>(Size(10,20), FFTWDCTEngine<float, FFTWFloatPlan>::Forward));
  subject->input()->FillBy(1.0);
  boost::shared_ptr<ArrayInterface<float> > output(subject->Execute());
  EXPECT_EQ(1.0, output->content(Position(0,0)));
}
