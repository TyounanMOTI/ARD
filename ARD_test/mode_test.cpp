#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <pressure.h>
#include <mode_map.h>

using namespace ARD;

TEST(ModeMap, InverseDCT) {
  boost::scoped_ptr<ModeMap> subject(new ModeMap(20, 10));
  boost::scoped_ptr<Pressure> pressure(subject->InverseDCT());
  EXPECT_TRUE(pressure->Size() == subject->Size());
}

TEST(ModeMap, Size) {
  boost::scoped_ptr<ModeMap> subject(new ModeMap(20, 10));
  EXPECT_TRUE(subject->Size() == 200);
}