#include <gtest/gtest.h>
#include <fftw_double_dct_engine.h>
#include <fftw_array.h>

using namespace ARD;

TEST(FFTWDoubleDCTEngineTest, DCTDirectCurrent) {
  boost::shared_ptr<DCTEngine<double> > subject(new FFTWDoubleDCTEngine(Size(10,20), FFTWDoubleDCTEngine::Forward));
  subject->input()->FillBy(1.0);
  boost::shared_ptr<ArrayInterface<double> > output(subject->Execute());
  EXPECT_EQ(1.0, output->content(Position(0,0)));
}
