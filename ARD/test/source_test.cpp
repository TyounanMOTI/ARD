#include <gtest/gtest.h>
#include <source.h>
#include <fftw_double_dct_engine_factory.h>

using namespace ARD;

class SourceTest : public testing::Test
{
protected:
  typedef boost::shared_ptr<Source<double> > SourcePointer;
  typedef boost::shared_ptr<DCTEngineFactory<double> > DCTEngineFactoryPointer;
  typedef boost::shared_ptr<ForceField<double> > ForceFieldPointer;
  virtual void SetUp() {
    position = Position(0,0);
  }

  Position position;
  std::vector<double> content;
  SourcePointer subject;
};

TEST_F(SourceTest, Pop) {
  content.push_back(5.0);
  content.push_back(1.0);
  subject.reset(new Source<double>(position, content));
  EXPECT_EQ(5.0, subject->Pop());
  EXPECT_EQ(1.0, subject->Pop());
}

TEST_F(SourceTest, EmptyPop) {
  subject.reset(new Source<double>(position, content));
  EXPECT_EQ(0, subject->Pop());
}

TEST_F(SourceTest, Emit) {
  content.push_back(5.0);
  subject.reset(new Source<double>(position, content));
  DCTEngineFactoryPointer engine_factory(new FFTWDoubleDCTEngineFactory());
  ForceFieldPointer force(new ForceField<double>(Size(20,10), engine_factory));
  subject->Emit(force);
  EXPECT_EQ(5.0, force->content(position));
}
