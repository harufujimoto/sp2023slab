#include <iostream>
#include <vector>

#include "./../src/practice.cpp"

int main() {
  std::vector<long> a = {
      3, 4, 10, 100, 1000000000LL, 10000000001LL, 10000000002LL, 10000000003LL};

  for (int i = 0; i < (int)a.size(); i++) {
    std::cout << "Case #" << i << ": ";
    long res;
    sum(res, a[i]);
    long expected = a[i] * (a[i] + 1) / 2;
    if (res == expected) {
      std::cout << "OK" << std::endl;
    } else {
      std::cout << "ERROR" << std::endl;
      std::cout << "atcual : " << res << std::endl;
      std::cout << "expected : " << expected << std::endl;
    }
  }
}
