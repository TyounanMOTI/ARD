#include <gtest/gtest.h>
#include <boost/multi_array.hpp>

TEST(MultiArrayTest, GetElementType) {
  ::testing::StaticAssertTypeEq<boost::multi_array<int, 3>::element, int>();
}
