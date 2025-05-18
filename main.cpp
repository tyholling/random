#include <bitset>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <memory>

using namespace std;

uint32_t xors(uint32_t x) {
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

// check: xors has 2^32 - 1 nonzero values
void test() {
  auto bits = make_unique<bitset<0x1'0000'0000>>();
  bits->set(0);

  uint32_t i = 0;
  uint32_t x = 1;
  printf("i: %08x x: %08x\n", i, x);

  uint32_t step = 0x1000'0000;
  uint32_t next = 0x0fff'ffff;
  for (i = 1; i; ++i) {
    x = xors(x);
    if (i == next) {
      printf("i: %08x x: %08x\n", i, x);
      next += step;
    }
    bits->set(x);
  }
  assert(x == 1);

  printf("bits count: %11lx\n", bits->count());
  assert(bits->count() == bits->size());
}

int main() { test(); }
