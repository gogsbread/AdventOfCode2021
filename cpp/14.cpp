#include "common.h"

namespace {
using Polymer = std::string;
using Insertions = std::unordered_map<std::string, char>;
std::pair<Polymer, Insertions> parse(const vs &input) {
  auto it = input.begin();
  Polymer p(*it);
  std::advance(it, 1);
  char c1[3], c2[2];
  Insertions ins;
  for (; it != input.end(); ++it) {
    sscanf((*it).c_str(), "%s -> %s", c1, c2);
    ins[std::string(c1)] = c2[0];
  }
  return std::make_pair(p, ins);
}

long p(const vs &input, size_t steps) {
  const auto [polymer, insertions] = parse(input);
  std::unordered_map<std::string, long> pc1{};
  std::unordered_map<std::string, long> pc2{};
  std::unordered_map<char, long> groups{};
  for (size_t i = 0; i < polymer.size() - 1; ++i) {
    const std::string s =
        std::string(1, polymer[i]) + std::string(1, polymer[i + 1]);
    pc1[s] += 1;
    groups[polymer[i + 1]] -= 1;
  }
  groups[polymer.back()] += 1;

  for (size_t _ = 0; _ < steps; ++_) {
    auto &pc = (!pc1.empty()) ? pc1 : pc2;
    auto &npc = (!pc1.empty()) ? pc2 : pc1;
    while (!pc.empty()) {
      const auto it = pc.begin();
      const auto &[polymer, count] = *it;
      if (insertions.find(polymer) != insertions.end()) {
        const auto &b = insertions.at(polymer);
        std::string s1 = std::string(1, polymer[0]) + std::string(1, b);
        std::string s2 = std::string(1, b) + std::string(1, polymer[1]);
        npc[s1] += count;
        npc[s2] += count;
        groups[b] -= count;
      } else {
        npc[polymer] = count;
      }
      pc.erase(it);
    }
  }
  auto &pc = (!pc1.empty()) ? pc1 : pc2;
  for (const auto &p : pc) {
    const auto count = p.second;
    for (const auto &c : p.first) {
      groups[c] += count;
    }
  }

  const auto &max = std::max_element(
      groups.begin(), groups.end(),
      [](const auto &v1, const auto &v2) { return v1.second < v2.second; });
  const auto &min = std::min_element(
      groups.begin(), groups.end(),
      [](const auto &v1, const auto &v2) { return v1.second < v2.second; });
  return (*max).second - (*min).second;
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p(input, 10)));
  gb::advent2020::writeOut(std::to_string(p(input, 40)));
}