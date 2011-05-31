#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <pressure.h>
#include <size.h>

using namespace ARD;

class PressureTest : public testing::Test {
protected:
  virtual void SetUp() {
    size = Size(30, 10);
    subject = PressurePtr(new Pressure(size));
  }

  typedef boost::shared_ptr<Pressure> PressurePtr;
  PressurePtr subject;
  Size size;
};

TEST_F(PressureTest, GetSize) {
  EXPECT_EQ(subject->GetSize(), size);
}

TEST_F(PressureTest, DCT) {
  EXPECT_EQ(subject->DCT()->GetSize(), subject->GetSize());
}