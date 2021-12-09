#include <algorithm>
#include <bitset>
#include <cstdio>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using vs = std::vector<std::string>;

namespace gb::advent2020 {
std::vector<std::string> readIn() {
  std::vector<std::string> lines;
  for (std::string l; getline(std::cin, l);) {
    lines.emplace_back(l);
  }
  return lines;
}

void writeOut(std::string s) { std::cout << s << std::endl; }
} // namespace gb::advent2020