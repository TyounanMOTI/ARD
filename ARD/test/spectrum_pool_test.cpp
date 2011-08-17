#include <gtest/gtest.h>
#include <spectrum_pool.h>
#include <fftw_double_dct_engine_factory.h>

using namespace ARD;

TEST(SpectrumPoolTest, UpdateReturnsPressureSpectrum) {
  Size size(20,10);
  boost::shared_ptr<ForceSpectrum<double> > force(new ForceSpectrum<double>(boost::shared_ptr<ArrayInterface<double> >(new FFTWArray<double>(size))));
  boost::shared_ptr<DCTEngineFactory<double> > engine_factory(new FFTWDoubleDCTEngineFactory());
  boost::shared_ptr<SpectrumPool<double> > subject(new SpectrumPool<double>(size, 0.0001, engine_factory));
  boost::shared_ptr<PressureSpectrum<double> > result(subject->Update(force));
  EXPECT_EQ(0.0, result->content(Position(0,0)));
}
