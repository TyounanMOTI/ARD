#include <gtest/gtest.h>
#include <source.h>
#include <fftw_dct_engine_factory.h>

using namespace ARD;

class SourceTest : public testing::Test
{
protected:
  virtual void SetUp() {
    position = Position(0,0);
  }

  Position position;
  std::vector<Power> content;
  SourcePointer subject;
};

TEST_F(SourceTest, Pop) {
  content.push_back(Power(5.0));
  content.push_back(Power(1.0));
  subject.reset(new Source(position, content));
  EXPECT_EQ(Power(5.0), subject->Pop());
  EXPECT_EQ(Power(1.0), subject->Pop());
}

TEST_F(SourceTest, EmptyPop) {
  subject.reset(new Source(position, content));
  EXPECT_EQ(Power(0.0), subject->Pop());
}

TEST_F(SourceTest, Emit) {
  content.push_back(Power(5.0));
  subject.reset(new Source(position, content));
  DCTEngineFactoryPointer engine_factory(new FFTWDCTEngineFactory());
  ForceFieldPointer force(new ForceField(Size(20,10), engine_factory));
  subject->Emit(force);
  EXPECT_EQ(Power(5.0), force->content()->content(position));
}
