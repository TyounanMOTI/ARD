#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <size.h>

using namespace ARD;

TEST(SizeTest, WidthHeight) {
  boost::scoped_ptr<Size> subject(new Size(20, 10));
  EXPECT_TRUE(subject->width == 20);
  EXPECT_TRUE(subject->height == 10);
}

TEST(SizeTest, Euqality) {
  Size subject(20, 10);
  Size other(10, 20);
  EXPECT_FALSE(subject == other);
}
