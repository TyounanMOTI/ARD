#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
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

TEST_F(PressureMapTest, DCTReturnSameSize) {
  boost::scoped_ptr<ModeMap> transformed(subject->DCT());
  EXPECT_EQ(transformed->size(), subject->size());
}

TEST_F(PressureMapTest, Record) {
  MicrophonePointer mic(new Microphone(Position(2,1)));
  subject->set_content(Position(2,1), Pressure(10));
  subject->Record(mic);
  EXPECT_EQ(Pressure(10), mic->content().back());
}
