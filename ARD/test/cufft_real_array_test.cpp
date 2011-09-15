#include <gtest/gtest.h>
#include <cufft_real_array.h>

using namespace ARD;

class CufftRealArrayTest : public testing::Test
{
  typedef boost::shared_ptr<CufftRealArray> ArrayPointer;

protected:
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
