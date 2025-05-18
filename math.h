#pragma once

#include <cstdint>

uint32_t xors(uint32_t x) {
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}
