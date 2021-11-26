#include <iostream>
#include <vector>

#include "common.h"

namespace gb::advent2020 {
void p1(const std::vector<std::string> &input) {
  for (auto &l : input) {
    std::cout << l << std::endl;
  }
}
} // namespace gb::advent2020

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::p1(input);
}