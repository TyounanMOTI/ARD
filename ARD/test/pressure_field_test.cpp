#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <pressure_field.h>
#include <size.h>
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

TEST_F(PressureFieldTest, Record) {
  MicrophonePointer mic(new Microphone(Position(2,1)));
  subject->set_content(Position(2,1), Pressure(10));
  subject->Record(mic);
  EXPECT_EQ(Pressure(10), mic->content().back());
}
