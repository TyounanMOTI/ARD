#include <gtest/gtest.h>
#include <spectrum_pool.h>

using namespace ARD;

TEST(SpectrumPoolTest, UpdateReturnsPressureField) {
  SpectrumPoolPointer subject(new SpectrumPool());
  PressureFieldPointer result = subject->Update();
  EXPECT_EQ(Pressure(0.0), result->content(Position(0,0)));
}
