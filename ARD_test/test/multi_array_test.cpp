#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <multi_array.h>

using namespace ARD;

TEST(MultiArrayTest, GetSize) {
  Size size(20, 10);
  boost::scoped_ptr<MultiArray> subject(new MultiArray(size));
  
  EXPECT_EQ(subject->GetSize(), size);
}
