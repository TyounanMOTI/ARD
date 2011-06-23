#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <pressure_field.h>
#include <pressure_spectrum.h>
#include <mode_coefficient.h>
#include "plot/output_fftw_array.h"

using namespace ARD;

class PressureSpectrumTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(20, 10);
    subject = PressureSpectrumPointer(new PressureSpectrum(size));
  }

  PressureSpectrumPointer subject;
  Size size;
};

TEST_F(PressureSpectrumTest, InitializeWithFFTWArrayContent) {
  FFTWArrayContent content(static_cast<Precision*>(fftw_malloc(sizeof(Precision)*size.Length())),
                            fftw_free);
  content[0] = Precision(1.0);
  PressureSpectrumPointer mode_map(new PressureSpectrum(size, content));
  EXPECT_EQ(Precision(1.0), mode_map->content(Position(0,0)));
//  OutputFFTWReal2DArray(size.width(), size.height(), mode_map->get());
}

TEST_F(PressureSpectrumTest, InverseDCTReturnsSameSize) {
  PressureFieldPointer transformed(subject->InverseDCT());
  EXPECT_EQ(subject->size(), transformed->size());
}

TEST_F(PressureSpectrumTest, InverseDCTForDataOnlyValueOnHead) {
  subject->set_content(Position(0,0), ModeCoefficient(1.0));
  PressureFieldPointer transformed(subject->InverseDCT());
  EXPECT_EQ(Pressure(1.0), transformed->content(Position(0,0)));
  EXPECT_EQ(Pressure(1.0), transformed->content(Position(10,9)));
//  OutputFFTWReal2DArray(size.width(), size.height(), transformed->get());
}
