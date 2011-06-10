#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <multi_array.h>

using namespace ARD;

class MultiArrayTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(20, 10);
    subject = MultiArrayPtr(new MultiArray(size));
  }
  
  Size size;
  typedef boost::shared_ptr<MultiArray> MultiArrayPtr;
  MultiArrayPtr subject;
};

TEST_F(MultiArrayTest, GetSize) {
  EXPECT_EQ(subject->GetSize(), size);
}

TEST_F(MultiArrayTest, GetArrayElement) {
  subject->SetData(Position(0,0), Pressure(0.0));
  EXPECT_EQ(subject->GetData(Position(0,0)), Pressure(0.0));
}

TEST_F(MultiArrayTest, SetArrayElement) {
  subject->SetData(Position(0,0), Pressure(1.0));
  EXPECT_EQ(subject->GetData(Position(0,0)), Pressure(1.0));
}
