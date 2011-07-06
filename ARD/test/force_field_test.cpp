#include <gtest/gtest.h>
#include <force_field.h>
#include <mode_coefficient.h>
#include "plot/output_fftw_array.h"

using namespace ARD;

class ForceFieldTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(10, 20);
    subject = ForceFieldPointer(new ForceField(size));
  }
  
  Size size;
  ForceFieldPointer subject;
};

TEST_F(ForceFieldTest, DCT) {
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

TEST_F(ForceFieldTest, EmitSound) {
  std::vector<Power> content;
  content.push_back(Power(2.0));
  SourcePointer source(new Source(Position(7,7), content));
  subject->EmitSound(source);
  EXPECT_EQ(Power(2.0), subject->content(Position(7,7)));
}
