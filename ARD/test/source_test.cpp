#include <gtest/gtest.h>
#include <source.h>
#include <fftw_multi_array.h>

using namespace ARD;

class SourceTest : public testing::Test
{
protected:
  typedef Source<float> FloatSource;
  typedef boost::shared_ptr<FloatSource> SourcePointer;

  virtual void SetUp() {
    position = Position(0,0);
  }

  Position position;
  FloatSource::Content content;
  SourcePointer subject;
};

TEST_F(SourceTest, Pop) {
  content.push_back(5.0);
  content.push_back(1.0);
  subject.reset(new FloatSource(position, content));
  EXPECT_EQ(5.0, subject->Pop());
  EXPECT_EQ(1.0, subject->Pop());
}

TEST_F(SourceTest, EmptyPop) {
  subject.reset(new FloatSource(position, content));
  EXPECT_EQ(0, subject->Pop());
}
