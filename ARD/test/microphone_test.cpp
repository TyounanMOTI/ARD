#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <microphone.h>

using namespace ARD;

class MicrophoneTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject = MicrophonePointer(new Microphone(Position(2, 1)));
  }

  MicrophonePointer subject;
};

TEST_F(MicrophoneTest, InitialContentShouldEmpty) {
  EXPECT_TRUE(subject->content().empty());
}

TEST_F(MicrophoneTest, Push) {
  subject->Push(Pressure(10));
  subject->Push(Pressure(5));
  EXPECT_EQ(Pressure(5), subject->content().back());
}

TEST_F(MicrophoneTest, Pop) {
  subject->Push(Pressure(10));
  subject->Push(Pressure(30));
  subject->Push(Pressure(50));
  subject->Pop(2);
  EXPECT_EQ(50, subject->content().back());
}
