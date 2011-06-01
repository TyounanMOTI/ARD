#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <pressure_map.h>
#include <size.h>

using namespace ARD;

class PressureMapTest : public testing::Test {
protected:
  virtual void SetUp() {
    size = Size(30, 10);
    subject = PressureMapPtr(new PressureMap(size));
  }

  typedef boost::shared_ptr<PressureMap> PressureMapPtr;
  PressureMapPtr subject;
  Size size;
};

TEST_F(PressureMapTest, DCT) {
  EXPECT_EQ(subject->DCT()->GetSize(), subject->GetSize());
}