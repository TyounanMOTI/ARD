#include <gtest/gtest.h>
#include <whole_field_microphone.h>

using namespace ARD;

TEST(WholeFieldMicrophoneTest, Record) {
  WholeFieldMicrophonePointer subject(new WholeFieldMicrophone());
  PressureFieldPointer field(new PressureField(Size(20,20)));
  field->set_content(Position(10,10), Pressure(20.0));

  subject->Record(field);
  EXPECT_EQ(Pressure(20.0), subject->Pop()->content(Position(10,10)));
}
