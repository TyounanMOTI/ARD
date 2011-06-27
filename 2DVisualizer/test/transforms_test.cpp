#include <gtest/gtest.h>
#include <transforms.h>

TEST(TransformsTest, QuantizeToUint8) {
  double max = 10.0;
  double min = -10.0;
  EXPECT_EQ(0, quantize_to_uint8(min, max));
  EXPECT_EQ(127, quantize_to_uint8(0.0, max));
  EXPECT_EQ(254, quantize_to_uint8(max, max));
}
