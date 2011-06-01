#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <size.h>

using namespace ARD;

class SizeTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject = Size(20, 10);
  }

  Size subject;
};

TEST_F(SizeTest, Euqality) {
  Size other(10, 20);
  EXPECT_FALSE(subject == other);
}

TEST_F(SizeTest, Length) {
  EXPECT_EQ(subject.Length(), 200);
}
