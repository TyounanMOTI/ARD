#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <fftw_array.h>

using namespace ARD;

class FFTWArrayTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(20, 10);
    subject = FFTWArrayPointer(new FFTWArray(size));
  }
  
  Size size;
  FFTWArrayPointer subject;
};

TEST_F(FFTWArrayTest, Copy) {
  subject->set_content(Position(1,2), Precision(10.0));
  FFTWArrayPointer p_copied(new FFTWArray(*subject));
  EXPECT_EQ(Precision(10.0), p_copied->content(Position(1,2)));
  subject->set_content(Position(1,2), Precision(5.0));
  EXPECT_EQ(Precision(10.0), p_copied->content(Position(1,2)));
}

TEST_F(FFTWArrayTest, GetSize) {
  EXPECT_EQ(size, subject->size());
}

TEST_F(FFTWArrayTest, GetRawPointer) {
  Precision* out = subject->get();
  out[Position(1,2).Serialize(subject->size())] = Precision(10.0);
  EXPECT_EQ(Precision(10.0), subject->content(Position(1,2)));
}

TEST_F(FFTWArrayTest, GetArrayElement) {
  subject->set_content(Position(0,0), Precision(0.0));
  EXPECT_EQ(Precision(0.0), subject->content(Position(0,0)));
}

TEST_F(FFTWArrayTest, SetArrayElement) {
  subject->set_content(Position(0,0), Precision(1.0));
  EXPECT_EQ(Precision(1.0), subject->content(Position(0,0)));
}

TEST_F(FFTWArrayTest, FillByZero) {
  subject->FillByZero();
  EXPECT_EQ(Precision(0.0), subject->content(Position(0,0)));
  EXPECT_EQ(Precision(0.0), subject->content(Position(19,9)));
}

TEST_F(FFTWArrayTest, FillBy) {
  subject->FillBy(Precision(10.0));
  EXPECT_EQ(Precision(10.0), subject->content(Position(0,0)));
  EXPECT_EQ(Precision(10.0), subject->content(Position(5,2)));
}

TEST_F(FFTWArrayTest, DivideInPlace) {
  subject->FillBy(Precision(5.0));
  (*subject) /= 5;
  EXPECT_EQ(Precision(1.0), subject->content(Position(0,0)));
  EXPECT_EQ(Precision(1.0), subject->content(Position(5,2)));
}
