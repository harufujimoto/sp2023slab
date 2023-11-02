#include <iostream>
#include <vector>

#include "./../src/practice.cpp"

int main() {
  const long P = 998244353;
  const long a = 2023;

  std::vector<long> n = {0,     1,      10,      100,      1000,
                         10000, 100000, 1000000, 10000000, long(1e12)};
  std::vector<long> z = {1,         2023,     329969289, 340092910, 800061172,
                         820078466, 47962465, 363599901, 836634156, 596422706};

  int cnt = 0;
  for (int i = 0; i < (int)n.size(); i++) {
    std::cout << "Case #" << i << ": ";
    long res;
    pow(res, a, n[i], P);
    if (res == z[i]) {
      std::cout << "OK" << std::endl;
      cnt++;
    } else {
      std::cout << "ERROR" << std::endl;
      std::cout << "actual : " << res << std::endl;
      std::cout << "expected : " << z[i] << std::endl;
    }
  }

  std::cout << cnt << "/" << (int)n.size() << " cases passed" << std::endl;
  if (cnt != (int)n.size()) {
    exit(-1);
  }
}
