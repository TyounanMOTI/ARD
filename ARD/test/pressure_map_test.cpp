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
    subject = PressureMapPointer(new PressureMap(size));
  }
  
  PressureMapPointer subject;
  Size size;
};

TEST_F(PressureMapTest, DCTReturnSameSize) {
  ModeMapPointer transformed(subject->DCT());
  EXPECT_EQ(subject->size(), transformed->size());
}

TEST_F(PressureMapTest, DCTForDirectCurrent) {
  for (int y = 0; y < size.height(); y++) {
    for (int x = 0; x < size.width(); x++) {
      subject->set_content(Position(x,y), Pressure(1.0));
    }
  }
  ModeMapPointer transformed(subject->DCT());
  EXPECT_EQ(ModeCoefficient(size.Length()*2*2*1.0), transformed->content(Position(0,0)));
  EXPECT_EQ(ModeCoefficient(0.0), transformed->content(Position(19,9)));
}

TEST_F(PressureMapTest, Record) {
  MicrophonePointer mic(new Microphone(Position(2,1)));
  subject->set_content(Position(2,1), Pressure(10));
  subject->Record(mic);
  EXPECT_EQ(Pressure(10), mic->content().back());
}
