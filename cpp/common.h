#include <iostream>
#include <map>
#include <vector>

namespace gb::advent2020 {
std::vector<std::string> readIn() {
  std::vector<std::string> lines;
  for (std::string l; getline(std::cin, l);) {
    lines.emplace_back(l);
  }
  return lines;
}
} // namespace gb::advent2020