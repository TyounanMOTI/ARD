#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <scene.h>
#include <size.h>

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

TEST_F(SceneTest, Update) {
  Signal signal(subject->Update());
  EXPECT_EQ(0, signal.size());
}

TEST_F(SceneTest, InitializeWithSize) {
  EXPECT_EQ(size, subject->size());
}
