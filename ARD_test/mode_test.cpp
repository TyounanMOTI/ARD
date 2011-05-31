#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <pressure.h>
#include <mode_map.h>

using namespace ARD;

TEST(ModeMap, InverseDCT) {
  boost::scoped_ptr<ModeMap> subject(new ModeMap());
  boost::scoped_ptr<Pressure> pressure(subject->InverseDCT());
  EXPECT_TRUE(pressure->Size() == subject->Size());
}
