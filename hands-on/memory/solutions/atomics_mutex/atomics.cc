#include <atomic>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
// compile with -O3
// FIX THIS CODE!
int main() {
  const std::size_t N = 1000000;
  std::vector<int> data(N, 0);

  //create a flag for telling me when the producer is ready
  std::atomic<bool> ready = false;
  // Producer: fill data, then write
  auto producer = [&] {
    for (std::size_t i = 0; i < N; ++i) {
      data[i] = i;
    }
    ready.store(true, std::memory_order_release);
  };

  //consumer, sum the elements
  auto consumer = [&] {
    while (ready.load(std::memory_order_acquire) == false) {
      // spinning
    }
    long long s = 0;
    for (std::size_t i = 0; i < N; ++i) {
      s += data[i];
    }

    // Expected sum if data[i] = i
    long long expected = static_cast<long long>(N) * (N - 1) / 2;
    std::cout << "Sum=" << s << " expected=" << expected << std::endl;
    if (s == expected) {
      std::cout << "CORRECT! " << std::endl;
    } else {
      std::cout << "Try Again! " << std::endl;
    }
  };

  std::thread tP(producer);
  std::thread tC(consumer);
  tP.join();
  tC.join();
}
