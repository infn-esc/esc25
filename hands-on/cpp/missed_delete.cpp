
using SomeType = int;

SomeType* factory();
void do_something(SomeType*);

int main()
{
  auto t = factory();

  // try {

  do_something(t);

  delete t;

  // } catch (...) {
  // }
}

SomeType* factory()
{
  return new SomeType{};
}

void do_something(SomeType*)
{
  throw 1;
}
