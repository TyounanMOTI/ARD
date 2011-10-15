#include <gtest/gtest.h>
#include <whole_field_microphone.h>
#include <fftw_array.h>

using namespace ARD;

class WholeFieldMicrophoneTest : public testing::Test
{
protected:
  typedef boost::shared_ptr<WholeFieldMicrophone<double> > WholeFieldMicrophonePointer;
  typedef boost::shared_ptr<ArrayInterface<double> > ArrayInterfacePointer;
  typedef boost::shared_ptr<PressureField<double> > PressureFieldPointer;
  
  virtual void SetUp() {
    subject.reset(new WholeFieldMicrophone<double>());
    size = Size(20,20);
    field.reset(new PressureField<double>(ArrayInterfacePointer(new FFTWArray<double>(size))));
  }

  Size size;
  WholeFieldMicrophonePointer subject;
  PressureFieldPointer field;
};

TEST_F(WholeFieldMicrophoneTest, Record) {
  field->set_content(Position(10,10), 20.0);
  subject->Record(field);

  PressureFieldPointer result(new PressureField<double>(ArrayInterfacePointer(new FFTWArray<double>(size))));
  subject->Plot(result);
  EXPECT_EQ(20.0, result->content(Position(10,10)));
}

TEST_F(WholeFieldMicrophoneTest, RecordCopiesField) {
  field->set_content(Position(10,10), 20.0);
  subject->Record(field);
  field->set_content(Position(10,10), 10.0);

  PressureFieldPointer result(new PressureField<double>(ArrayInterfacePointer(new FFTWArray<double>(size))));
  subject->Plot(result);
  EXPECT_EQ(20.0, result->content(Position(10,10)));
}

TEST_F(WholeFieldMicrophoneTest, Plot) {
  field->set_content(Position(10,10), 20.0);
  field->set_content(Position(0,0), 5.0);
  subject->Record(field);
  
  PressureFieldPointer result(new PressureField<double>(ArrayInterfacePointer(new FFTWArray<double>(size))));
  subject->Plot(result);
  EXPECT_EQ(20.0, result->content(Position(10,10)));
  EXPECT_EQ(5.0, result->content(Position(0,0)));
}

TEST_F(WholeFieldMicrophoneTest, PlotEmpty) {
  PressureFieldPointer result(new PressureField<double>(ArrayInterfacePointer(new FFTWArray<double>(size))));
  subject->Plot(result);
  EXPECT_EQ(0.0, result->content(Position(0,0)));
}
