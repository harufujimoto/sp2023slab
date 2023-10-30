#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct pubkey {
  long p, g, y;
};
using seckey = long;
using cipher = std::array<long, 2>;
using message = long;

std::random_device rd;
std::mt19937 rng(rd());

namespace elgamal {

void enc(pubkey &pk, message &msg, cipher &c) {
  assert(0 < msg && msg < pk.p);
  // edit here!
}

void dec(pubkey &pk, seckey &sk, cipher &c, message &res) {
  // edit here!
}

}  // namespace elgamal

