#include <gtest/gtest.h>
#include <spectrum_pool.h>
#include <mode_coefficient.h>

using namespace ARD;

TEST(SpectrumPoolTest, UpdateReturnsPressureSpectrum) {
  Size size(20,10);
  ForceSpectrumPointer force(new ForceSpectrum(size));
  SpectrumPoolPointer subject(new SpectrumPool(size, 0.0001));
  PressureSpectrumPointer result = subject->Update(force);
  EXPECT_EQ(ModeCoefficient(0.0), result->content(Position(0,0)));
}
