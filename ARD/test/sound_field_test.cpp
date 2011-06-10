#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <sound_field.h>

using namespace ARD;

TEST(SoundField, Update) {
  boost::scoped_ptr<SoundField> subject(new SoundField());
  Signal signal(subject->Update());
  EXPECT_TRUE(signal.length == 0);
}
