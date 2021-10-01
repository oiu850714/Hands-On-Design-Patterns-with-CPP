#include <iostream>

template <typename T>
class ArrayOf2 {
public:
  T& operator[](size_t i) noexcept { return a_[i]; }
  const T& operator[](size_t i) const noexcept { return a_[i]; }
  T sum() const { return a_[0] + a_[1]; }
private:
  T a_[2];
};

int main() {
  ArrayOf2<int> i;
  i[0] = 1;
  i[1] = 5;
  std::cout << i.sum() << "\n";
  ArrayOf2<double> x;
  x[0] = -3.5;
  x[1] = 4;
  std::cout << x.sum() << "\n";

  ArrayOf2<char*> c; char s[] = "Hello";
  c[0] = s; c[1] = s + 2;
  // std::cout << c.sum() << "\n";
  // ArratOf2<char*> is valid as long as ArrayOf2<char*>::sum is not called
}
