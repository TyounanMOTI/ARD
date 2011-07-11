#include <gtest/gtest.h>
#include <spectrum_pool.h>
#include <mode_coefficient.h>

using namespace ARD;

TEST(SpectrumPoolTest, UpdateReturnsPressureSpectrum) {
  SpectrumPoolPointer subject(new SpectrumPool());
  PressureSpectrumPointer result = subject->Update();
  EXPECT_EQ(ModeCoefficient(0.0), result->content(Position(0,0)));
}
