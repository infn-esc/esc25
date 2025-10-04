#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void count_even_odd(const std::vector<int>& x, int& even_count,
                    int& odd_count) {
  const std::size_t N = x.size();
  const unsigned n_threads = 4;

  even_count = 0;
  odd_count = 0;

  std::mutex m;  // protects even_count and odd_count

  // count locally, then merge once under the lock
  // dont keep updating the atomic in the loop!
  auto worker = [&](std::size_t begin, std::size_t end) {
    int local_even = 0;
    int local_odd = 0;

    for (std::size_t i = begin; i < end; ++i) {
      if ((x[i] & 1) == 0)
        ++local_even;
      else
        ++local_odd;
    }

    std::lock_guard<std::mutex> lk(m);
    even_count += local_even;
    odd_count += local_odd;
  };

  // Split work into chunks
  const std::size_t chunk = (N + n_threads - 1) / n_threads;

  std::vector<std::thread> threads;
  threads.reserve(n_threads);

  for (unsigned t = 0; t < n_threads; ++t) {
    std::size_t begin = t * chunk;
    if (begin >= N)
      break;
    std::size_t end = std::min(N, begin + chunk);
    threads.emplace_back(worker, begin, end);
  }

  for (auto& th : threads)
    th.join();
}

int main() {
  std::vector<int> x(100);
  for (int i = 0; i < 100; i++)
    x[i] = i;

  int even = 0, odd = 0;
  count_even_odd(x, even, odd);

  std::cout << "Even: " << even << " Odd: " << odd << "\n";
  return 0;
}
