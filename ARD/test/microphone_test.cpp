#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <microphone.h>
#include <signal.h>

using namespace ARD;

TEST(MicrophoneTest, InitialContentShouldEmpty) {
  MicrophonePointer mic(new Microphone(Position(2, 1)));
  EXPECT_TRUE(mic->Content().empty());
}

TEST(MicrophoneTest, Push) {
  MicrophonePointer subject(new Microphone(Position(2,1)));
  subject->Push(Pressure(10));
  EXPECT_EQ(subject->Content().front(), Pressure(10));
}
