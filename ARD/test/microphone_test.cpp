#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <microphone.h>
#include <signal.h>

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
  EXPECT_TRUE(subject->Content().empty());
}

TEST_F(MicrophoneTest, Push) {
  subject->Push(Pressure(10));
  subject->Push(Pressure(5));
  EXPECT_EQ(subject->Content().back(), Pressure(5));
}
