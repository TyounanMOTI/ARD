#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <pressure.h>

using namespace ARD;

TEST(Pressure, Size) {
  boost::scoped_ptr<Pressure> subject(new Pressure(30, 10));
  EXPECT_TRUE(subject->Size() == 300);
}

TEST(Pressure, DCT) {
  boost::scoped_ptr<Pressure> subject(new Pressure(30, 10));
  EXPECT_TRUE(subject->DCT()->Size() == subject->Size());
}