#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <pressure_field.h>
#include <pressure_spectrum.h>
#include "fftw_double_dct_engine_factory.h"
#include "plot/output_fftw_array.h"

using namespace ARD;

class PressureSpectrumTest : public testing::Test
{
protected:
  typedef boost::shared_ptr<DCTEngineFactory<double> > DCTEngineFactoryPointer;
  typedef boost::shared_ptr<PressureSpectrum<double> > PressureSpectrumPointer;
  typedef boost::shared_ptr<PressureField<double> > PressureFieldPointer;
  
  virtual void SetUp() {
    size = Size(20, 10);
    DCTEngineFactoryPointer engine_factory(new FFTWDoubleDCTEngineFactory());
    subject = PressureSpectrumPointer(new PressureSpectrum<double>(size, engine_factory));
  }

  PressureSpectrumPointer subject;
  Size size;
};

TEST_F(PressureSpectrumTest, InitializeWithFFTWArray) {
  subject->set_content(Position(0,0), 1.0);
  PressureSpectrumPointer result(new PressureSpectrum<double>(*subject));
  EXPECT_EQ(1.0, result->content(Position(0,0)));
//  OutputFFTWReal2DArray(size.width(), size.height(), mode_map->get());
}

TEST_F(PressureSpectrumTest, InverseDCTReturnsSameSize) {
  PressureFieldPointer transformed(subject->InverseDCT());
  EXPECT_EQ(subject->size(), transformed->size());
}

TEST_F(PressureSpectrumTest, InverseDCTForDataOnlyValueOnHead) {
  subject->set_content(Position(0,0), 1.0);
  PressureFieldPointer transformed(subject->InverseDCT());
  EXPECT_EQ(1.0, transformed->content(Position(0,0)));
  EXPECT_EQ(1.0, transformed->content(Position(10,9)));
//  OutputFFTWReal2DArray(size.width(), size.height(), transformed->get());
}
