#include <gtest/gtest.h>
#include <fftw_dct_engine_factory.h>

using namespace ARD;

TEST(FFTWDCTEngineFactoryTest, GenerateEngine) {
  FFTWDCTEngineFactoryPointer factory(new FFTWDCTEngineFactory());
  FFTWDCTEnginePointer engine(factory->GenerateEngine(Size(10,20), FFTWDCTEngine::Forward));
  engine->input()->set_content(Position(1,2), Precision(10.0));
  EXPECT_EQ(Precision(10.0), engine->input()->content(Position(1,2)));
}
