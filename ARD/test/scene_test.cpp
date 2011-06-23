#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <scene.h>

using namespace ARD;

TEST(SceneTest, Update) {
  boost::scoped_ptr<Scene> subject(new Scene());
  Signal signal(subject->Update());
  EXPECT_EQ(0, signal.size());
}
