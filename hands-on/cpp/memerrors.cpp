#include <iostream>

void f(int n, char const* arg)
{
  std::cout << "n = " << n << ", prog = " << arg << '\n';
}

int main(int, char* argv[])
{
  int x;
  f(x, argv[0]);
  int* p = new int;
  f(*p, argv[2]);
}
