#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <pressure_field.h>
#include <size.h>
#include "plot/output_fftw_array.h"

using namespace ARD;

class PressureFieldTest : public testing::Test {
protected:
  virtual void SetUp() {
    size = Size(30, 10);
    subject = PressureFieldPointer(new PressureField(FFTWArrayPointer(new FFTWArray(size))));
  }
  
  PressureFieldPointer subject;
  Size size;
};
