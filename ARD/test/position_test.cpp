#include <gtest/gtest.h>
#include <position.h>

using namespace ARD;

TEST(PositionTest, Serialize) {
  Position subject(3, 2);
  EXPECT_EQ(23, subject.Serialize(Size(10, 5)));
}
