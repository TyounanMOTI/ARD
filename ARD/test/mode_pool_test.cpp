#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <spectrum_pool.h>

using namespace ARD;

TEST(SpectrumPoolTest, UpdateReturnsSuppliedMicrophone) {
  SpectrumPoolPointer subject(new SpectrumPool());

  MicrophonePointer mic(new Microphone(Position(5, 3)));
  MicrophonePointer result(subject->Update(mic));

  EXPECT_EQ(result, mic);
}
