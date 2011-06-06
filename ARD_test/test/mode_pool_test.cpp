#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <mode_pool.h>

using namespace ARD;

TEST(ModePoolTest, Update) {
  boost::scoped_ptr<ModePool> subject(new ModePool());

  typedef boost::shared_ptr<Microphone> MicrophonePointer;
  MicrophonePointer mic(new Microphone(Position(5, 3)));
  MicrophonePointer result(subject->Update(mic));

  EXPECT_EQ(mic, result);
}
