#include <gtest/gtest.h>
#include <force_field.h>
#include <fftw_dct_engine_factory.h>

using namespace ARD;

class ForceFieldTest : public testing::Test
{
protected:
  typedef boost::shared_ptr<ForceField<double> > ForceFieldPointer;
  typedef boost::shared_ptr<ForceSpectrum<double> > ForceSpectrumPointer;
  
  virtual void SetUp() {
    size = Size(10, 20);
    boost::shared_ptr<DCTEngineFactory<double> > engine_factory(new FFTWDCTEngineFactory<double>());
    subject = ForceFieldPointer(new ForceField<double>(size, engine_factory));
  }
  
  Size size;
  ForceFieldPointer subject;
};

TEST_F(ForceFieldTest, DCT) {
  for (int y = 0; y < size.height(); y++) {
    for (int x = 0; x < size.width(); x++) {
      subject->set_content(Position(x,y), 1.0);
    }
  }

  ForceSpectrumPointer output(subject->DCT());
  EXPECT_EQ(1.0, output->content(Position(0,0)));
  EXPECT_EQ(0.0, output->content(Position(9,19)));
}
