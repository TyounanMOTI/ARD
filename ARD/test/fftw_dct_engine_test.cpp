#include <gtest/gtest.h>
#include <fftw_dct_engine.h>

using namespace ARD;

TEST(FFTWDCTEngineTest, DCTDirectCurrent) {
  FFTWDCTEnginePointer subject(new FFTWDCTEngine(Size(10,20), FFTWDCTEngine::Forward));
  subject->input()->FillBy(Precision(1.0));
  ArrayInterfacePointer output(subject->Execute());
  EXPECT_EQ(Precision(1.0), output->content(Position(0,0)));
}
