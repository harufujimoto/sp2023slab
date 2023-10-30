#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <string>

#include "./../src/elgamal.cpp"

struct args {
  int k;
  message msg;
};

void prepare(vector<args>& out, const string FN) {
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
    arg.msg = stoi(str);
    out.emplace_back(arg);
  }
}

int main(int argc, char* argv[]) {
  const string FN = argv[1];

  cout << "FILENAME : " << FN << endl;

  int correct = 0;

  vector<args> testcase;
  prepare(testcase, FN);
  int T = (int)testcase.size();

  for (int i = 0; i < T; i++) {
    args arg = testcase[i];
    pubkey pk;
    seckey sk;
    elgamal::key_gen(arg.k, pk, sk);
    cipher c;
    elgamal::enc(pk, arg.msg, c);
    message res;
    elgamal::dec(pk, sk, c, res);
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
  if(correct != T){
    exit(-1);
  }
}
