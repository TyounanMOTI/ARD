#include <gtest/gtest.h>
#include <source.h>
#include <fftw_multi_array.h>
#include <boost/assign.hpp>

using namespace boost::assign;
using namespace ARD;

class SourceTest : public testing::Test
{
protected:
  typedef Source<float> FloatSource;
  typedef boost::shared_ptr<FloatSource> SourcePointer;

  virtual void SetUp() {
    position += 0,0;
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

TEST_F(SourceTest, Emit) {
  content += 1,2,3;
  subject.reset(new FloatSource(position, content));
  FFTWFloat2DArray field(boost::extents[20][10]);
  subject->Emit(field);
  EXPECT_EQ(1, field(position));
  subject->Emit(field);
  EXPECT_EQ(2, field(position));
}
