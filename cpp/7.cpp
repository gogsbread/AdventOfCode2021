#include "common.h"

namespace {
std::vector<long> splitoncomma(const std::string &s) {
  std::istringstream ss(s);
  std::vector<long> ts;
  for (std::string p; std::getline(ss, p, ',');) {
    ts.emplace_back(std::stol(p));
  }
  return ts;
}

long p1(const std::string crabs) {
  std::vector<long> pos = splitoncomma(crabs);
  std::sort(pos.begin(), pos.end());
  long median = pos[pos.size() / 2];
  long t = 0;
  for (const auto &p : pos)
    t += std::abs(p - median);
  return t;
}

long p2(const std::string crabs) {
  std::vector<long> pos = splitoncomma(crabs);
  float mean =
      (float)std::accumulate(pos.begin(), pos.end(), 0L) / (float)pos.size();
  long pos1 = std::floor(mean);
  long pos2 = std::ceil(mean);

  std::array<long, 2> fuel{};
  size_t i = 0;
  for (const auto &bp : {pos1, pos2}) {
    auto &f = fuel[i];
    for (const auto &p : pos) {
      f += ((std::abs(p - bp) * (std::abs(p - bp) + 1)) / 2);
    }
    ++i;
  }
  return std::min(fuel[0], fuel[1]);
}

} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input[0])));
  gb::advent2020::writeOut(std::to_string(p2(input[0])));
}