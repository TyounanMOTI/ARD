#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <vector>
#include <signal.h>

using namespace ARD;

TEST(SignalTest, InitializeWithContent) {
  std::vector<short> content;
  content.push_back(5);
  boost::scoped_ptr<Signal> subject(new Signal(content));
  std::vector<short> output = subject->Content();
  EXPECT_EQ(output[0], 5);
}
