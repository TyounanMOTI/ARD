#include <gtest/gtest.h>
#include <signal.h>

using namespace ARD;

TEST(SignalTest, Pop) {
  long length = 3;
  SignalContent input(new SignalLevel[length]);
  input[0] = SignalLevel(100);
  input[1] = SignalLevel(50);
  SignalPointer subject(new Signal(input, length));
  EXPECT_EQ(SignalLevel(100), subject->Pop());
  EXPECT_EQ(SignalLevel(50), subject->Pop());
}
