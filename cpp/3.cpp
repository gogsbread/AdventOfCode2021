#include "common.h"

namespace {
long conv(const std::string &s) {
  long r = 0;
  size_t n = s.size();
  for (size_t i = 0; i < s.size(); ++i) {
    const char &c = s[n - i - 1];
    r |= ((c == '1') ? 1 : 0) << i;
  }
  return r;
}

long p1(const vs &input) {
  long gam = 0;
  int n = input.size();
  for (size_t i = 0, d = 1; i < input[0].size(); ++i, d <<= 1) {
    int one = 0;
    for (const auto &s : input) {
      one += ((conv(s) & d) > 0) ? 1 : 0;
    }
    int zero = n - one;
    gam |= ((one > zero) ? 1 : 0) << i;
  }
  long ep = ~gam & ((1 << input[0].size()) - 1);
  return gam * ep;
}

template <class Comp> long life(std::set<std::string> s, int i, Comp comp) {
  size_t n = s.size();
  if (n == 1)
    return conv(*s.begin());

  int one = 0;
  for (auto &e : s) {
    one += (e[i] == '1') ? 1 : 0;
  }
  int zero = n - one;
  char c = comp(one, zero) ? '1' : '0';
  auto it = s.begin();
  while (it != s.end()) {
    if ((*it)[i] != c) {
      it = s.erase(it);
    } else
      ++it;
  }

  return life(s, ++i, comp);
}

long p2(const vs &input) {
  std::set<std::string> s(input.begin(), input.end());
  long oxy = life(s, 0, std::greater_equal<long>());
  long co2 = life(s, 0, std::less<long>());
  return oxy * co2;
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}