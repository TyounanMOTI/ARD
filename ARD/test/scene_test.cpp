#include <gtest/gtest.h>
#include <scene.h>
#include <fftw_multi_array.h>
#include <direct_reference_microphone.h>
#include <point_source.h>

using namespace ARD;

class SceneTest : public testing::Test
{
protected:
  typedef DirectReferenceMicrophone<FFTWFloat2DArray> Mic;
  typedef PointSource<FFTWFloat2DArray> Src;

  virtual void SetUp() {
    subject.reset(new Scene<FFTWFloat2DArray>(boost::extents[30][20]));
    microphone.reset(new Mic());
    subject->AddMicrophone(microphone);
  }

  std::shared_ptr<Mic> microphone;
  std::unique_ptr<Scene<FFTWFloat2DArray> > subject;
};

TEST_F(SceneTest, EmitRecordTest) {
  std::shared_ptr<Src> source(new Src(Position({0, 0}), std::deque<float>({1.0f, 0.0f})));
  subject->AddSource(source);

  std::deque<std::shared_ptr<Microphone<FFTWFloat2DArray> > > microphones = subject->Update();
  EXPECT_EQ(microphone, microphones.front());
  EXPECT_FLOAT_EQ(1.0f/(30*20), microphones.front()->Pop()[0][0]);
}
