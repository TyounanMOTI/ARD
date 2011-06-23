#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <scene.h>
#include <size.h>

using namespace ARD;

TEST(SceneTest, Update) {
  Size size(20, 10);
  ScenePointer subject(new Scene(size));
  Signal signal(subject->Update());
  EXPECT_EQ(0, signal.size());
}

TEST(SceneTest, InitializeWithSize) {
  Size size(20, 10);
  ScenePointer subject(new Scene(size));
  EXPECT_EQ(size, subject->size());
}
