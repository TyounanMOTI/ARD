#include <gtest/gtest.h>

TEST(LambdaTest, LambdaUsable) {
  auto func = [](int a) { return a + 1; };
  EXPECT_EQ(2, func(1));
}
