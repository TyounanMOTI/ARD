#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <pressure_map.h>
#include <mode_map.h>
#include "output_fftw_array.h"

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

TEST_F(ModeMapTest, InitializeWithMultiArrayContent) {
  MultiArrayContent content(static_cast<Precision*>(fftw_malloc(sizeof(Precision)*size.Length())),
                            fftw_free);
  content[0] = Precision(1.0);
  ModeMapPointer mode_map(new ModeMap(size, content));
  EXPECT_EQ(Precision(1.0), mode_map->content(Position(0,0)));
//  OutputFFTWReal2DArray(size.width(), size.height(), mode_map->get());
}

TEST_F(ModeMapTest, InverseDCTReturnsSameSize) {
  PressureMapPointer transformed(subject->InverseDCT());
  EXPECT_EQ(subject->size(), transformed->size());
}

TEST_F(ModeMapTest, InverseDCTForDataOnlyValueOnHead) {
  subject->set_content(Position(0,0), ModeCoefficient(1.0));
  PressureMapPointer transformed(subject->InverseDCT());
  EXPECT_EQ(Pressure(1.0), transformed->content(Position(0,0)));
  EXPECT_EQ(Pressure(1.0), transformed->content(Position(10,9)));
//  OutputFFTWReal2DArray(size.width(), size.height(), transformed->get());
}
