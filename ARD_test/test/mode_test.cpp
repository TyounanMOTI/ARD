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
    subject = ModeMapPtr(new ModeMap(20, 10));
  }

  typedef boost::shared_ptr<ModeMap> ModeMapPtr;
  ModeMapPtr subject;
};

TEST_F(ModeMapTest, InverseDCT) {
  boost::scoped_ptr<Pressure> pressure(subject->InverseDCT());
  EXPECT_TRUE(pressure->Size() == subject->Size());
}

TEST_F(ModeMapTest, Size) {
  EXPECT_TRUE(subject->Size() == 200);
}