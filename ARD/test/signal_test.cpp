#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <stdexcept>
#include <signal.h>

using namespace ARD;

class SignalTest : public testing::Test {
protected:
  virtual void SetUp() {
    content.push_back(5);
    subject = Signal(content);
  }

  SignalContent content;
  Signal subject;
};

TEST_F(SignalTest, InitializeWithContent) {
  SignalContent output = subject.content();
  EXPECT_EQ(5, output[0]);
}

TEST_F(SignalTest, ContentIsClonedAtInitialization) {
  content.push_back(10);
  EXPECT_THROW(subject.at(1), std::out_of_range);
}

TEST_F(SignalTest, At) {
  EXPECT_EQ(5, subject.at(0));
}
