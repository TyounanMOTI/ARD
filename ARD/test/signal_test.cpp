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
  std::vector<short> output = subject->Content();
  EXPECT_EQ(output[0], 5);
}
