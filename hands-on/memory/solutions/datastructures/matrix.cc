#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

template <typename TResolution>
class Timer {
 public:
  Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

  void reset() { start_time_ = std::chrono::high_resolution_clock::now(); }

  double elapsed() const {
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, TResolution> elapsed_time =
        end_time - start_time_;
    return elapsed_time.count();
  }

 private:
  std::chrono::high_resolution_clock::time_point start_time_;
};

void matmul_naive_ijk(const double* A, const double* B, double* R, int N) {
  std::fill(R, R + N * N, 0.0);
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      double s = 0.0;
      for (int k = 0; k < N; ++k)
        s += A[i * N + k] * B[k * N + j];
      R[i * N + j] = s;
    }
}

void matmul_ikj(const double* A, const double* B, double* R, int N) {
  std::fill(R, R + N * N, 0.0);
  for (int i = 0; i < N; ++i)
    for (int k = 0; k < N; ++k) {
      double aik = A[i * N + k];
      for (int j = 0; j < N; ++j)
        R[i * N + j] += aik * B[k * N + j];
    }
}

int main() {
  const int N = 1024;
  std::vector<double> A(N * N), B(N * N), R(N * N);
  std::mt19937_64 rng(0);
  std::uniform_real_distribution<> d(-1, 1);
  for (auto& x : A)
    x = d(rng);
  for (auto& x : B)
    x = d(rng);

  // warm-up
  matmul_ikj(A.data(), B.data(), R.data(), N);

  // choose one to profile:
  Timer<std::milli> timer;
  matmul_naive_ijk(A.data(), B.data(), R.data(), N);

  std::cout << "Time taken: " << timer.elapsed() << " milliseconds"
            << std::endl;

  timer.reset();
  //  matmul_ikj(A.data(), B.data(), R.data(), N);

  std::cout << "Time taken: " << timer.elapsed() << " milliseconds"
            << std::endl;
}
