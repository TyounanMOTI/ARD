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
  EXPECT_EQ(size, subject->size());
}

TEST_F(MultiArrayTest, GetArrayElement) {
  subject->set_content(Position(0,0), Precision(0.0));
  EXPECT_EQ(Precision(0.0), subject->content(Position(0,0)));
}

TEST_F(MultiArrayTest, SetArrayElement) {
  subject->set_content(Position(0,0), Precision(1.0));
  EXPECT_EQ(Precision(1.0), subject->content(Position(0,0)));
}

TEST_F(MultiArrayTest, InitializeWithFFTWComplexArray) {
  MultiArrayContent content = MultiArrayContent(static_cast<double*>(fftw_malloc(sizeof(double)*size.Length())),
                                fftw_free);
  content[MultiArrayIndexFromPosition(Position(5,3), size)] = Precision(1.0);
  subject = MultiArrayPointer(new MultiArray(size, content));
  EXPECT_EQ(Precision(1.0), subject->content(Position(5,3)));
  
  // still can change content's value?
  subject->set_content(Position(5,3), Precision(5.0));
  EXPECT_EQ(Precision(5.0), subject->content(Position(5,3)));
}

