#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <pressure.h>
#include <mode_map.h>

using namespace ARD;

class ModeMapTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(20, 10);
    subject = ModeMapPtr(new ModeMap(size));
  }

  typedef boost::shared_ptr<ModeMap> ModeMapPtr;
  ModeMapPtr subject;
  Size size;
};

TEST_F(ModeMapTest, InverseDCT) {
  boost::scoped_ptr<Pressure> pressure(subject->InverseDCT());
  EXPECT_EQ(pressure->GetSize(), subject->GetSize());
}

TEST_F(ModeMapTest, GetSize) {
  EXPECT_EQ(subject->GetSize(), size);
}