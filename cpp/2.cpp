#include "common.h"

namespace {
long p1(const vs &input) {
  struct P {
    long x;
    long y;
  };
  P p{};
  for (const auto &l : input) {
    std::istringstream ss(l);
    std::string cmd, arg;
    ss >> cmd >> arg;
    if (cmd == "forward") {
      p.x += std::stol(arg);
    } else if (cmd == "down") {
      p.y += std::stol(arg);
    } else { // up
      p.y -= std::stol(arg);
    }
  }
  return p.x * p.y;
}

long p2(const vs &input) {
  struct P {
    long h;
    long d;
    long a;
  };
  P p{};
  for (const auto &l : input) {
    std::istringstream ss(l);
    std::string cmd, arg;
    ss >> cmd >> arg;
    if (cmd == "forward") {
      p.h += std::stol(arg);
      p.d += p.a * std::stol(arg);
    } else if (cmd == "down") {
      p.a += std::stol(arg);
    } else { // up
      p.a -= std::stol(arg);
    }
  }
  return p.d * p.h;
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}