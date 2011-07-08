#include <gtest/gtest.h>
#include <whole_field_microphone.h>

using namespace ARD;

class WholeFieldMicrophoneTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject.reset(new WholeFieldMicrophone());
    field.reset(new PressureField(Size(20,20)));
  }

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
