#include <gtest/gtest.h>
#include <valarray>

TEST(ValarrayTest, InitializeWithRawPointer) {
  int *p = (int*)malloc(sizeof(int)*10);
  p[0] = 4;
  ASSERT_EQ(4, p[0]);

  std::valarray<int> subject(p, 10);
  ASSERT_EQ(4, subject[0]);

  p[0] = 6;
  //  EXPECT_EQ(6, subject[0]);  // FAIL!

  free(p);
}
