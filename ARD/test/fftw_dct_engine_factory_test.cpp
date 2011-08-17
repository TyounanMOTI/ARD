#include <gtest/gtest.h>
#include <fftw_dct_engine_factory.h>

using namespace ARD;

TEST(FFTWDCTEngineFactoryTest, GenerateForwardEngineDouble) {
  boost::shared_ptr<DCTEngineFactory<double> > factory(new FFTWDCTEngineFactory<double>());
  boost::shared_ptr<DCTEngine<double> > engine(factory->GenerateForwardEngine(Size(10,20)));
  engine->input()->set_content(Position(1,2), 10.0);
  EXPECT_EQ(10.0, engine->input()->content(Position(1,2)));
}
