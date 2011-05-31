#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <pressure.h>

using namespace ARD;

class PressureTest : public testing::Test {
protected:
  virtual void SetUp() {
    subject = PressurePtr(new Pressure(30,10));
  }

  typedef boost::shared_ptr<Pressure> PressurePtr;
  PressurePtr subject;
};

TEST_F(PressureTest, Size) {
  EXPECT_TRUE(subject->Size() == 300);
}

TEST_F(PressureTest, DCT) {
  EXPECT_TRUE(subject->DCT()->Size() == subject->Size());
}