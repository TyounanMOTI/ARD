#include <gtest/gtest.h>
#include <whole_field_microphone.h>

using namespace ARD;

class WholeFieldMicrophoneTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject.reset(new WholeFieldMicrophone());
    size = Size(20,20);
    field.reset(new PressureField(size));
  }

  Size size;
  WholeFieldMicrophonePointer subject;
  PressureFieldPointer field;
};

TEST_F(WholeFieldMicrophoneTest, Record) {
  field->set_content(Position(10,10), Pressure(20.0));

  subject->Record(field);
  EXPECT_EQ(Pressure(20.0), subject->Pop()->content(Position(10,10)));
}

TEST_F(WholeFieldMicrophoneTest, RecordCopiesField) {
  field->set_content(Position(10,10), Pressure(20.0));
  subject->Record(field);
  field->set_content(Position(10,10), Pressure(10.0));
  EXPECT_EQ(Pressure(20.0), subject->Pop()->content(Position(10,10)));
}

TEST_F(WholeFieldMicrophoneTest, Plot) {
  field->set_content(Position(10,10), Pressure(20.0));
  field->set_content(Position(0,0), Pressure(5.0));
  subject->Record(field);
  
  PressureFieldPointer result(new PressureField(size));
  subject->Plot(result);
  EXPECT_EQ(Pressure(20.0), result->content(Position(10,10)));
  EXPECT_EQ(Pressure(5.0), result->content(Position(0,0)));
}
