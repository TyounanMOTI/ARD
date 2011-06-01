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
    subject = ModeMapPtr(new ModeMap(size));
  }

  typedef boost::shared_ptr<ModeMap> ModeMapPtr;
  ModeMapPtr subject;
  Size size;
};

TEST_F(ModeMapTest, InverseDCT) {
  boost::scoped_ptr<PressureMap> PressureMap(subject->InverseDCT());
  EXPECT_EQ(PressureMap->GetSize(), subject->GetSize());
}
