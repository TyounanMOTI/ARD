#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <scene.h>

using namespace ARD;

class SceneTest : public testing::Test
{
protected:
  virtual void SetUp() {
    size = Size(20, 10);
    subject = ScenePointer(new Scene(size));
  }

  Size size;
  ScenePointer subject;
};

TEST_F(SceneTest, UpdateReturnsMicrophone) {
  MicrophonePointer microphone = MicrophonePointer(new Microphone(Position(5,5)));
  subject->set_microphone(microphone);
  EXPECT_EQ(microphone, subject->Update());
}

TEST_F(SceneTest, InitializeWithSize) {
  EXPECT_EQ(size, subject->size());
}
