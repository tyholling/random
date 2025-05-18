#include <cassert>
#include <cstdint>
#include <cstdio>

uint32_t xors(uint32_t x) {
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

void test(uint32_t k) {
  uint32_t i = 0;
  uint32_t x = k;

  for (i = 1; i; ++i) {
    x = xors(x);
  }
  assert(x == k);
  printf("i: %08x x: %08x\n", i, x);
}

int main() {
  for (uint32_t i = 1; i < 9; ++i) {
    test(i);
  }
}
