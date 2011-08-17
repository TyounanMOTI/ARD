#include <gtest/gtest.h>
#include <fftw_double_dct_engine_factory.h>

using namespace ARD;

TEST(FFTWDoubleDCTEngineFactoryTest, GenerateForwardEngine) {
  boost::shared_ptr<DCTEngineFactory<double> > factory(new FFTWDoubleDCTEngineFactory());
  boost::shared_ptr<DCTEngine<double> > engine(factory->GenerateForwardEngine(Size(10,20)));
  engine->input()->set_content(Position(1,2), 10.0);
  EXPECT_EQ(10.0, engine->input()->content(Position(1,2)));
}
