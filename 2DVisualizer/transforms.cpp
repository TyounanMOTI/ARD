#include "transforms.h"

Uint8 quantize_to_uint8(double input, double max) {
  double output = input * 127 / max + 127;

  if (output > 255) {
    return 255;
  } else if (output < 0) {
    return 0;
  }

  return output;
}
