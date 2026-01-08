#include <cassert>

template <int N>
struct Fibonacci
{
  static int const value {Fibonacci<N-1>::value + Fibonacci<N-2>::value};
};

template <>
struct Fibonacci<1>
{
  static int const value {1};
};

template <>
struct Fibonacci<0>
{
  static int const value {0};
};

int main()
{
  assert(Fibonacci<0>::value == 0);
  assert(Fibonacci<1>::value == 1);
  assert(Fibonacci<5>::value == 5);
  assert(Fibonacci<10>::value == 55);
  assert(Fibonacci<12>::value == 144);
}
