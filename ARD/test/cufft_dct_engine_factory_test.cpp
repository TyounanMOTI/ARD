#include <gtest/gtest.h>
#include <cufft_dct_engine_factory.h>

using namespace ARD;

TEST(CufftDCTEngineFactoryTest, Initialization) {
  typedef boost::shared_ptr<DCTEngineFactory<float> > FactoryPointer;
  typedef boost::shared_ptr<DCTEngine<float> > DCTEnginePointer;

  FactoryPointer factory(new CufftDCTEngineFactory());
  DCTEnginePointer engine(factory->GenerateForwardEngine(Size(20,10)));
  engine->input()->set_content(Position(4,2), 5.0);
  EXPECT_EQ(5.0, engine->input()->content(Position(4,2)));
}
