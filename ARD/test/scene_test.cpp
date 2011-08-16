#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <scene.h>
#include <microphone.h>
#include <point_microphone.h>
#include <fftw_double_dct_engine_factory.h>

using namespace ARD;

class SceneTest : public testing::Test
{
protected:
  typedef boost::shared_ptr<FFTWDoubleDCTEngineFactory> FFTWDoubleDCTEngineFactoryPointer;
  typedef boost::shared_ptr<Scene<double> > ScenePointer;
  typedef boost::shared_ptr<Source<double> > SourcePointer;
  typedef boost::shared_ptr<Microphone<double> > MicrophonePointer;
  
  virtual void SetUp() {
    FFTWDoubleDCTEngineFactoryPointer fftw_dct_engine_factory(new FFTWDoubleDCTEngineFactory());
    size = Size(20, 10);
    subject = ScenePointer(new Scene<double>(size, 0.001, fftw_dct_engine_factory));
    std::vector<double> source_content;
    source.reset(new Source<double>(Position(2,3), source_content));
    microphone.reset(new PointMicrophone<double>(Position(2,3)));
    subject->set_source(source);
    subject->set_microphone(microphone);
  }

  Size size;
  ScenePointer subject;
  SourcePointer source;
  MicrophonePointer microphone;
};

TEST_F(SceneTest, UpdateReturnsMicrophone) {
  MicrophonePointer microphone(new PointMicrophone<double>(Position(5,5)));
  subject->set_microphone(microphone);
  EXPECT_EQ(microphone, subject->Update());
}

TEST_F(SceneTest, Initialize) {
  EXPECT_EQ(size, subject->size());
}
