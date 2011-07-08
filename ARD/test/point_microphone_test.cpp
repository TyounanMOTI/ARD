#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <point_microphone.h>
#include <pressure_field.h>

using namespace ARD;

class PointMicrophoneTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject.reset(new PointMicrophone(Position(2,1)));
    size = Size(10,20);
    field.reset(new PressureField(size));
  }

  PointMicrophonePointer subject;
  Size size;
  PressureFieldPointer field;
};

TEST_F(PointMicrophoneTest, InitialContentShouldEmpty) {
  EXPECT_TRUE(subject->content().empty());
}

TEST_F(PointMicrophoneTest, Record) {
  field->set_content(Position(2,1), Pressure(10));
  subject->Record(field);
  EXPECT_EQ(Pressure(10), subject->content().back());
}

TEST_F(PointMicrophoneTest, Pop) {
  field->set_content(Position(2,1), Pressure(10));
  subject->Record(field);
  field->set_content(Position(2,1), Pressure(20));
  subject->Record(field);
  EXPECT_EQ(Pressure(10), subject->Pop());
  EXPECT_EQ(Pressure(20), subject->Pop());
}

TEST_F(PointMicrophoneTest, Plot) {
  field->set_content(Position(2,1), Pressure(10));
  subject->Record(field);
  PressureFieldPointer result(new PressureField(size));
  subject->Plot(result);

  EXPECT_EQ(Pressure(10), result->content(Position(2,1)));
}
