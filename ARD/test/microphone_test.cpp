#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <microphone.h>
#include <signal.h>

using namespace ARD;

TEST(MicrophoneTest, InitialContentShouldEmpty) {
  MicrophonePointer mic(new Microphone(Position(2, 1)));
  boost::scoped_ptr<Signal> content(mic->Content());
  EXPECT_EQ(content->length, 0);
}
