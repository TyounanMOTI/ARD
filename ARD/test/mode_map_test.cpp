#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <pressure_map.h>
#include <mode_map.h>

using namespace ARD;

class ModeMapTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(20, 10);
    subject = ModeMapPointer(new ModeMap(size));
  }

  ModeMapPointer subject;
  Size size;
};

TEST_F(ModeMapTest, InverseDCT) {
  PressureMapPointer transformed(subject->InverseDCT());
  EXPECT_EQ(transformed->size(), subject->size());
}
