///////////////////////////////////////////////////
///////////// DON'T TOUCH THIS FILE ////////////////
///////////////////////////////////////////////////
/*
Step.1
elgamal.cpp の elgamal::dec() 関数を記述する。
(注)
画面左側の「コンパイル時オプション」に -D=LARGE と書いて実行すると
大きい値を入力値としてテストを実行できる。
*/
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

#include "./elgamal.cpp"

#ifdef LARGE
#define FN "./large.txt"
#else
#define FN "./small.txt"
#endif

struct args {
  int k;
  pubkey pk;
  seckey sk;
  message msg;
  cipher c;
};

void prepare(vector<args>& out) {
  std::ifstream ifs(FN);
  if (!ifs) {
    cerr << "file open error" << endl;
    exit(1);
  }
  string input, str;
  getline(ifs, input);
  if (input.back() == '\n') {
    input = input.substr(0, input.size() - 1);
  }
  int T = stoi(input);
  for (int i = 0; i < T; i++) {
    args arg;
    getline(ifs, input);
    stringstream ss{input};
    getline(ss, str, ' ');
    arg.k = stoi(str);
    getline(ss, str, ' ');
    arg.pk.p = stoi(str);
    getline(ss, str, ' ');
    arg.pk.g = stoi(str);
    getline(ss, str, ' ');
    arg.pk.y = stoi(str);
    getline(ss, str, ' ');
    arg.sk = stoi(str);
    getline(ss, str, ' ');
    arg.msg = stoi(str);
    getline(ss, str, ' ');
    arg.c[0] = stoi(str);
    getline(ss, str, ' ');
    arg.c[1] = stoi(str);
    out.emplace_back(arg);
  }
}

int main() {
  cout << "FILENAME : " << FN << endl;

  int correct = 0;

  vector<args> testcase;
  prepare(testcase);

  int T = (int)testcase.size();
  for (int i = 0; i < T; i++) {
    args arg = testcase[i];
    message res;
    elgamal::dec(arg.pk, arg.sk, arg.c, res);
    cout << "Case #" << i << " : ";
    if (arg.msg != res) {
      cout << "ERROR" << endl;
      cout << "actual : " << res << endl;
      cout << "expected : " << arg.msg << endl;
    } else {
      cout << "OK" << endl;
      correct++;
    }
  }

  cout << correct << "/" << T << " cases passed." << endl;
}
