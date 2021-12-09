#include "common.h"

namespace {
vs splitoncomma(const std::string &s) {
  std::istringstream ss(s);
  vs ts;
  for (std::string p; std::getline(ss, p, ',');) {
    ts.emplace_back(p);
  }
  return ts;
}

long p(const std::string init_fishes, size_t days) {
  std::array<long, 9> fishes{};
  for (const auto &f : splitoncomma(init_fishes))
    fishes[std::stol(f)] += 1;

  for (size_t i = 0; i < days; ++i) {
    long t = fishes[0];
    for (size_t j = 1; j < fishes.size(); ++j) {
      fishes[j - 1] = fishes[j];
    }
    fishes[8] = t;
    fishes[6] += t;
  }

  return std::accumulate(fishes.begin(), fishes.end(), 0L);
}

// long p2(const vs &input) {}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p(input[0], 80)));
  gb::advent2020::writeOut(std::to_string(p(input[0], 256)));
}