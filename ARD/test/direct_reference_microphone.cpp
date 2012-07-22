#include <gtest/gtest.h>
#include <direct_reference_microphone.h>
#include <fftw_multi_array.h>

using namespace ARD;

TEST(DirectReferenceMicrophoneTest, RecordTest) {
  FFTWFloat2DArray input(boost::extents[30][20]);
  input[10][10] = 10.0f;
  DirectReferenceMicrophone<FFTWFloat2DArray> subject;
  subject.Record(input);
  EXPECT_EQ(10.0f, subject.Pop()[10][10]);
}
