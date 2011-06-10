#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <signal.h>

using namespace ARD;

class SignalTest : public testing::Test {
protected:
  virtual void SetUp() {
    content.push_back(5);
    subject = SignalPointer(new Signal(content));
  }

  typedef std::vector<short> Content;
  typedef boost::shared_ptr<Signal> SignalPointer;
  Content content;
  SignalPointer subject;
};

TEST_F(SignalTest, InitializeWithContent) {
  Content output = subject->Content();
  EXPECT_EQ(output[0], 5);
}

TEST_F(SignalTest, ContentIsClonedAtInitialization) {
  content.push_back(10);
  EXPECT_THROW(subject->at(1), std::out_of_range);
}

TEST_F(SignalTest, At) {
  EXPECT_EQ(subject->at(0), 5);
}
