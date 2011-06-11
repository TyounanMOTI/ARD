#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <multi_array.h>

using namespace ARD;

class MultiArrayTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(20, 10);
    subject = MultiArrayPointer(new MultiArray(size));
  }
  
  Size size;
  MultiArrayPointer subject;
};

TEST_F(MultiArrayTest, GetSize) {
  EXPECT_EQ(subject->size(), size);
}

TEST_F(MultiArrayTest, GetArrayElement) {
  subject->set_content(Position(0,0), Pressure(0.0));
  EXPECT_EQ(subject->content(Position(0,0)), Pressure(0.0));
}

TEST_F(MultiArrayTest, SetArrayElement) {
  subject->set_content(Position(0,0), Pressure(1.0));
  EXPECT_EQ(subject->content(Position(0,0)), Pressure(1.0));
}

TEST_F(MultiArrayTest, InitializeWithFFTWComplexArray) {
  FFTWComplexArray content = FFTWComplexArray(static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex)*size.Length())));
  content[MultiArrayIndexFromPosition(Position(5,3), size)][0] = Pressure(1.0);
  subject = MultiArrayPointer(new MultiArray(size, content));
  EXPECT_EQ(Pressure(1.0), subject->content(Position(5,3)));
}

