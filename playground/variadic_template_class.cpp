#include <iostream>

template <typename ...T> struct Group;

template <typename T1> struct Group<T1> {
  T1 t1_;
  Group() = default;
  explicit Group(const T1 &t1) : t1_(t1) {}
  explicit Group(T1 &&t1) : t1_(std::move(t1)) {}
  explicit operator const T1 &() const { return t1_; }
  explicit operator T1 &() { return t1_; }
};

template <typename T1, typename... T> struct Group<T1, T...> : Group<T...> {
  T1 t1_;
  Group() = default;
  explicit Group(const T1 &t1, T &&...t)
      : Group<T...>(std::forward<T>(t)...), t1_(t1) {}
  explicit Group(T1 &&t1, T &&...t)
      : Group<T...>(std::forward<T>(t)...), t1_(std::move(t1)) {}
  explicit operator const T1 &() const { return t1_; }
  explicit operator T1 &() { return t1_; }
};


class C1 {
public:
  operator int() {
    return 2;
  }
};

class C2 : public C1 {
public:
  operator int() {
    return 4;
  }
};

int main() {
  Group<int, int, int> g1(1, 3, 5);
  std::cout << static_cast<int>(g1) << "\n"; // output "1"
  // result depends on the order of the non-variadic and variadic template parameter
  // if the ctor declaration becomes Group(T &&... t, T1 &&t1)
  // then the output becomes "5"

  C2 c2;
  std::cout << static_cast<int>(c2) << "\n"; // output 4
}
