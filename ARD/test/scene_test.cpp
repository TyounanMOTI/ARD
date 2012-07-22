#include <gtest/gtest.h>
#include <scene.h>
#include <fftw_multi_array.h>
#include <direct_reference_microphone.h>

using namespace ARD;

class SceneTest : public testing::Test
{
protected:
  virtual void SetUp() {
    subject.reset(new Scene<FFTWFloat2DArray>(boost::extents[30][20]));
  }

  std::unique_ptr<Scene<FFTWFloat2DArray> > subject;
};

TEST_F(SceneTest, UpdateReturnsMicrophonesTest) {
  std::shared_ptr<DirectReferenceMicrophone<FFTWFloat2DArray> > microphone(new DirectReferenceMicrophone<FFTWFloat2DArray>());
  subject->AddMicrophone(microphone);
  std::deque<std::shared_ptr<Microphone<FFTWFloat2DArray> > > microphones = subject->Update();
  EXPECT_EQ(microphone, microphones.front());
}
