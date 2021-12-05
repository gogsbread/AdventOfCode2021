#include "common.h"

namespace {
int p1(const vs &input) {
  int r = 0, p = 0;
  for (const auto &l : input) {
    int c = std::stoi(l);
    r += (c > p) ? 1 : 0;
    p = c;
  }
  return r - 1;
}

int p2(const vs &input) {
  // ya, c++ is just garbage when you try to use functional primitives
  int r = 0;
  auto add = [](const int &acc, const std::string &b) {
    return acc + std::stoi(b);
  };
  auto si = input.begin();
  int p = std::accumulate(si, std::next(si, 3), 0, add);
  for (std::advance(si, 1); std::next(si, 3) != input.end();
       std::advance(si, 1)) {
    int c = std::accumulate(si, std::next(si, 3), 0, add);
    r += (c > p) ? 1 : 0;
    p = c;
  }
  r += (std::accumulate(si, std::next(si, 3), 0, add) > p) ? 1 : 0;
  return r;
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}