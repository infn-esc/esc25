
int* factory();

// "still reachable"
auto g = factory();

int main()
{
  // "definitely lost"
  auto t = factory();
}

int* factory()
{
  return new int;
}
