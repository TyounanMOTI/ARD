#include <gtest/gtest.h>
#include <fftw_dct_engine_factory.h>

using namespace ARD;

TEST(FFTWDCTEngineFactoryTest, GenerateForwardEngine) {
  FFTWDCTEngineFactoryPointer factory(new FFTWDCTEngineFactory());
  DCTEnginePointer engine(factory->GenerateForwardEngine(Size(10,20)));
  engine->input()->set_content(Position(1,2), Precision_t(10.0));
  EXPECT_EQ(Precision_t(10.0), engine->input()->content(Position(1,2)));
}
