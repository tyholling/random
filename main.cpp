#include <bitset>
#include <cassert>
#include <list>
#include <memory>
#include <thread>

#include "math.h"

using namespace std;

// check that first 0x0100'0000 values are distinct
void nums(uint32_t k) {
  auto bits = make_unique<bitset<0x1'0000'0000>>();
  bits->set(0);

  uint32_t i = 0;
  uint32_t x = k;

  for (i = 1; i < 0x0100'0000; ++i) {
    bits->set(x);
    x = xors(x);
  }

  assert(i == bits->count());
  printf("k: %08x nums: %08lx\n", k, bits->count());
}

int main() {
  list<thread> threads;
  threads.push_back(thread(nums, 1));
  threads.push_back(thread(nums, 2));
  threads.push_back(thread(nums, 3));
  threads.push_back(thread(nums, 4));
  threads.push_back(thread(nums, 5));
  threads.push_back(thread(nums, 6));
  threads.push_back(thread(nums, 7));
  threads.push_back(thread(nums, 8));

  for (auto &t : threads) {
    t.join();
  }
}
