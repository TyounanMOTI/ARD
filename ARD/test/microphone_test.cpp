#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <microphone.h>
#include <signal.h>

using namespace ARD;

TEST(MicrophoneTest, InitialContentShouldEmpty) {
  MicrophonePointer mic(new Microphone(Position(2, 1)));
  EXPECT_EQ(mic->Content().length, 0);
}

TEST(MicrophoneTest, InitializeWithContent) {
  std::vector<short> content;
  content.push_back(5);
  Signal input = Signal(content);
  MicrophonePointer mic(new Microphone(Position(2,1), input));
  EXPECT_EQ(mic->Content().at(0), 5);
}
