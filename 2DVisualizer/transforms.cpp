#include "transforms.h"

Uint8 quantize_to_uint8(double input, double max) {
  return input * 127 / max + 127;
}
