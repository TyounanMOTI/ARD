#include <gtest/gtest.h>
#include <force_field.h>
#include <mode_coefficient.h>
#include <power.h>
#include "plot/output_fftw_array.h"

using namespace ARD;

TEST(ForceFieldTest, DCT) {
  Size size(10, 20);
  ForceFieldPointer subject(new ForceField(size));

  for (int y = 0; y < size.height(); y++) {
    for (int x = 0; x < size.width(); x++) {
      subject->set_content(Position(x,y), Power(1.0));
    }
  }

  ForceSpectrumPointer output(subject->DCT());
  EXPECT_EQ(ModeCoefficient(1.0), output->content(Position(0,0)));
  EXPECT_EQ(ModeCoefficient(0.0), output->content(Position(9,19)));

//  OutputFFTWReal2DArray(size.width(), size.height(), output->get());
}
