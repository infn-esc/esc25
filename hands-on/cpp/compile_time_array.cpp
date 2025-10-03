#include <array>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

template <...>
void make_array_helper(...) {}

template <...>
auto make_array(...) {
  // Hint: you can use std::common_type to deduce the type of the array
}

int main() {
  auto array = make_array(1, 4, 5, 2, 8, 7);
  for (auto x : array) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}
