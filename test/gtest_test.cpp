#include <gtest/gtest.h>
#include <boost/strong_typedef.hpp>

BOOST_STRONG_TYPEDEF(float, Float);

TEST(GTestTest, FloatingPoint) {
  EXPECT_FLOAT_EQ(10.2f, Float(10.2f));
}
