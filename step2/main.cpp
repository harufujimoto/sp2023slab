///////////////////////////////////////////////////
///////////// DON'T TOUCH THIS FILE ////////////////
///////////////////////////////////////////////////
/*
Step.2
elgamal.cpp の elgamal::enc(), elgamal::dec() 関数を記述する。
(step.1 を解いた人は step.1 の dec() 関数はそのまま流用できる）
(注)
画面左側の「コンパイル時オプション」に -D=LARGE と書いて実行すると
大きい値を入力値としてテストを実行できる。
*/
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

#include "./elgamal_ans.cpp"

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
    out.emplace_back(arg);
  }
}

int main() {
  cout << "FILENAME : " << FN << endl;

  int correct = 0;

  vector<args> testcase;
  prepare(testcase);

  int T = (int)testcase.size();
  prepare(testcase);
  for (int i = 0; i < T; i++) {
    args arg = testcase[i];
    cipher c;
    elgamal::enc(arg.pk,arg.msg,c);
    message res;
    elgamal::dec(arg.pk, arg.sk, c, res);
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
