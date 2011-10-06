#include <gtest/gtest.h>
#include <position.h>
#include <boost/assign.hpp>

using namespace ARD;
using namespace boost::assign;

TEST(PositionTest, Initialize) {
  Position subject;
  subject += 1,2,3;
  EXPECT_EQ(3, subject.back());
}
