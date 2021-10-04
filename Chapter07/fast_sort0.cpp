#include <iostream>

struct yes {
  char c;
};

struct no {
  char c;
  yes c1;
};

static_assert(sizeof(yes) != sizeof(no), "Do something else for yes/no types");

template <typename T> yes test_sort(decltype(&T::sort));
template <typename T> no test_sort(...);

template <typename T, size_t s> struct fast_sort_helper; // incomplete

template <typename T> // specialization
struct fast_sort_helper<T, sizeof(yes)> {
  static void fast_sort(T &x) {
    std::cout << "Sorting with T::sort\n";
    x.sort();
  }
};

template <typename T> void fast_sort(T &x) {
  fast_sort_helper<T, sizeof(test_sort<T>(NULL))>::fast_sort(x);
}

class A {
public:
  void sort() {}
};

class C {
public:
  void f() {}
};

int main() {
  A a;
  fast_sort(a);
  // C c; fast_sort(c); // Does not compile
}