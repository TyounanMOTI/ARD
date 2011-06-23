#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <pressure_field.h>
#include <size.h>
#include <mode_coefficient.h>
#include "plot/output_fftw_array.h"

using namespace ARD;

class PressureFieldTest : public testing::Test {
protected:
  virtual void SetUp() {
    size = Size(30, 10);
    subject = PressureFieldPointer(new PressureField(size));
  }
  
  PressureFieldPointer subject;
  Size size;
};

TEST_F(PressureFieldTest, DCTReturnSameSize) {
  PressureSpectrumPointer transformed(subject->DCT());
  EXPECT_EQ(subject->size(), transformed->size());
}

TEST_F(PressureFieldTest, DCTForDirectCurrent) {
  for (int y = 0; y < size.height(); y++) {
    for (int x = 0; x < size.width(); x++) {
      subject->set_content(Position(x,y), Pressure(1.0));
    }
  }
  PressureSpectrumPointer transformed(subject->DCT());
  EXPECT_EQ(ModeCoefficient(1.0), transformed->content(Position(0,0)));
  EXPECT_EQ(ModeCoefficient(0.0), transformed->content(Position(19,9)));
  
//  OutputFFTWReal2DArray(subject->size().width(), subject->size().height(), transformed->get());
}

TEST_F(PressureFieldTest, Record) {
  MicrophonePointer mic(new Microphone(Position(2,1)));
  subject->set_content(Position(2,1), Pressure(10));
  subject->Record(mic);
  EXPECT_EQ(Pressure(10), mic->content().back());
}
