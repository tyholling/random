#include <condition_variable>
#include <cstdio>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

class AtomicQueue {
public:
  AtomicQueue(uint32_t capacity) : capacity(capacity) {}
  bool empty() {
    lock_guard<mutex> lock(mtx);
    return q->empty();
  }
  bool enqueue(uint32_t num, milliseconds duration) {
    {
      unique_lock<mutex> lock(mtx);
      if (!cv_producer.wait_for(lock, duration, [&] { return q->size() < capacity; })) {
        return false;
      }
      q->push(num);
    }
    cv_consumer.notify_one();
    return true;
  }
  bool dequeue(uint32_t &num, milliseconds duration) {
    {
      unique_lock<mutex> lock(mtx);
      if (!cv_consumer.wait_for(lock, duration, [&] { return !q->empty(); })) {
        return false;
      }
      num = q->front();
      q->pop();
    }
    cv_producer.notify_one();
    return true;
  }

private:
  const uint32_t capacity;
  mutex mtx;
  condition_variable cv_consumer;
  condition_variable cv_producer;
  unique_ptr<queue<uint32_t>> q = make_unique<queue<uint32_t>>();
};

void consume(uint32_t id, AtomicQueue &q, bool &run) {
  while (run) {
    uint32_t num = 0;
    if (q.dequeue(num, milliseconds(10))) {
      this_thread::sleep_for(milliseconds(10));
      if ((num & 0xff) == 0xff) {
        printf("%4x:  %04x\n", id, num);
      }
    }
  }
}

int main() {
  AtomicQueue q(0x100);
  bool run = true;

  vector<thread> threads;
  for (uint32_t id = 0; id < thread::hardware_concurrency(); ++id) {
    threads.emplace_back(consume, id, ref(q), ref(run));
  }

  for (uint32_t i = 0; i < 0x1000; ++i) {
    while (!q.enqueue(i, milliseconds(10)));
  }
  while (!q.empty());
  run = false;

  for (auto &t : threads) {
    t.join();
  }
}
