#include <gtest/gtest.h>
#include <cufft_real_array.h>
#include <array_interface.h>

using namespace ARD;

class CufftRealArrayTest : public testing::Test
{
protected:
  typedef boost::shared_ptr<CufftRealArray> ArrayPointer;
  typedef boost::shared_ptr<ArrayInterface<float> > ArrayInterfacePointer;

  virtual void SetUp() {
    size = Size(20, 10);
    subject.reset(new CufftRealArray(Size(20, 10)));
  }

  Size size;
  ArrayPointer subject;
};

TEST_F(CufftRealArrayTest, SetArrayElement) {
  subject->set_content(Position(5,2), 5.0);
  EXPECT_EQ(5.0, subject->content(Position(5,2)));
}

TEST_F(CufftRealArrayTest, Clone) {
  subject->set_content(Position(5,2), 5.0);
  ArrayInterfacePointer cloned = subject->Clone();
  EXPECT_EQ(5.0, cloned->content(Position(5,2)));

  subject->set_content(Position(5,2), 10.0);
  EXPECT_EQ(5.0, cloned->content(Position(5,2)));
}