#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <size.h>

using namespace ARD;

TEST(SizeTest, Euqality) {
  Size subject(20, 10);
  Size other(10, 20);
  EXPECT_FALSE(subject == other);
}

TEST(SizeTest, Length) {
  Size subject(20, 10);
  EXPECT_EQ(subject.Length(), 200);
}
