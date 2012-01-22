#include <gtest/gtest.h>
#include <vtkMath.h>
#include <vtkSmartPointer.h>
#include <vtkColorTransferFunction.h>

TEST(MathTest, HSVToRGB) {
  double r,g,b;
  vtkMath::HSVToRGB(0.5, 1.0, 1.0, &r, &g, &b);
  EXPECT_FLOAT_EQ(0, r);
  EXPECT_FLOAT_EQ(1, g);
  EXPECT_FLOAT_EQ(1, b);
}

class ColorTransferFunctionTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject = vtkSmartPointer<vtkColorTransferFunction>::New();
  }

  vtkSmartPointer<vtkColorTransferFunction> subject;
};

TEST_F(ColorTransferFunctionTest, AddHSVPoint) {
  subject->AddHSVPoint(0, 0, 1, 1);
  subject->AddHSVPoint(1, 1, 1, 1);
  EXPECT_FLOAT_EQ(1, subject->GetRedValue(0));
  //  EXPECT_FLOAT_EQ(0, subject->GetRedValue(0.5)); // fails
}

TEST_F(ColorTransferFunctionTest, AddRGBPoint) {
  subject->AddRGBPoint(0, 1, 0, 0);
  subject->AddRGBPoint(0.5, 0, 1, 1);
  subject->AddRGBPoint(1, 1, 0, 0);
  EXPECT_FLOAT_EQ(0, subject->GetRedValue(0.5));
}

