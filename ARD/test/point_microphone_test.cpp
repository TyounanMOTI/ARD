#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <point_microphone.h>
#include <pressure_field.h>
#include <fftw_array.h>

using namespace ARD;

class PointMicrophoneTest : public testing::Test
{
protected:
  typedef boost::shared_ptr<PointMicrophone<double> > PointMicrophonePointer;
  typedef boost::shared_ptr<PressureField<double> > PressureFieldPointer;
  typedef boost::shared_ptr<ArrayInterface<double> > ArrayInterfacePointer;
  
  virtual void SetUp() {
    position = Position(2,1);
    subject.reset(new PointMicrophone<double>(position));
    size = Size(10,20);
    field.reset(new PressureField<double>(ArrayInterfacePointer(new FFTWArray<double>(size))));
  }

  Position position;
  PointMicrophonePointer subject;
  Size size;
  PressureFieldPointer field;
};

TEST_F(PointMicrophoneTest, InitialContentShouldEmpty) {
  EXPECT_TRUE(subject->content().empty());
}

TEST_F(PointMicrophoneTest, Record) {
  field->set_content(position, 10.0);
  subject->Record(field);
  EXPECT_EQ(10.0, subject->content().back());
}

TEST_F(PointMicrophoneTest, Pop) {
  field->set_content(position, 10.0);
  subject->Record(field);
  field->set_content(position, 20.0);
  subject->Record(field);
  EXPECT_EQ(10.0, subject->Pop());
  EXPECT_EQ(20.0, subject->Pop());
}

TEST_F(PointMicrophoneTest_Pop_Test, EmptyPop) {
  EXPECT_EQ(0, subject->Pop());
}

TEST_F(PointMicrophoneTest, Plot) {
  field->set_content(position, 10.0);
  subject->Record(field);
  PressureFieldPointer result(new PressureField<double>(ArrayInterfacePointer(new FFTWArray<double>(size))));
  subject->Plot(result);

  EXPECT_EQ(10.0, result->content(position));
}
