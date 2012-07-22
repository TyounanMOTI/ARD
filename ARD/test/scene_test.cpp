#include <gtest/gtest.h>
#include <scene.h>
#include <fftw_multi_array.h>

using namespace ARD;

TEST(SceneTest, InitializeWithExtent) {
  Scene<FFTWFloat2DArray> scene(boost::extents[30][20]);
}
