#include <gtest/gtest.h>
#include <cufft_real_array.h>

using namespace ARD;

TEST(CufftRealArrayTest, SetArrayElement) {
  typedef boost::shared_ptr<CufftRealArray> ArrayPointer;
  ArrayPointer subject(new CufftRealArray(Size(20, 10)));
  subject->set_content(Position(5,2), 5.0);
  EXPECT_EQ(5.0, subject->content(Position(5,2)));
}
