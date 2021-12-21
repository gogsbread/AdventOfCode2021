#include "common.h"

namespace {
using Dot = std::pair<unsigned long, unsigned long>;
using Dots = std::set<Dot>;
using Fold = std::pair<std::string, unsigned long>;
using Folds = std::vector<Fold>;

std::tuple<Dots, Folds, unsigned long, unsigned long> parse(const vs &input) {
  Dots d;
  unsigned long maxx = 0, maxy = 0;
  auto it = input.begin();
  for (; !(*it).empty(); std::advance(it, 1)) {
    // for (const auto &l : input) {
    std::istringstream ss(*it);
    std::string s1, s2;
    std::getline(ss, s1, ',');
    std::getline(ss, s2, ',');
    unsigned long x = std::stol(s1);
    unsigned long y = std::stol(s2);
    maxx = std::max(x, maxx);
    maxy = std::max(y, maxy);
    d.insert(Dot(x, y));
  }
  Folds f;
  for (std::advance(it, 1); it != input.end(); std::advance(it, 1)) {
    char s;
    unsigned long d;
    std::sscanf((*it).c_str(), "fold along %c=%lu", &s, &d);
    f.emplace_back(Fold(std::string(1, s), d));
  }
  return std::make_tuple(d, f, maxx, maxy);
}

long p1(const vs &input) {
  auto [dots, folds, maxx, maxy] = parse(input);
  const auto &f = folds[0];
  for (auto &d : dots) {
    if (f.first == "y" && d.second > f.second) {
      dots.insert(Dot(d.first, 2 * f.second - d.second));
      maxy = f.second;
    } else if (f.first == "x" && d.first > f.second) {
      dots.insert(Dot(2 * f.second - d.first, d.second));
      maxx = f.second;
    }
  }

  long count = 0;
  for (const auto &d : dots) {
    if (d.first <= maxx && d.second <= maxy) {
      ++count;
    }
  }
  return count;
}

std::string p2(const vs &input) {
  auto [dots, folds, maxx, maxy] = parse(input);
  for (auto f : folds) {
    for (auto &d : dots) {
      if (f.first == "y" && d.second > f.second) {
        dots.insert(Dot(d.first, 2 * f.second - d.second));
        maxy = f.second;
      } else if (f.first == "x" && d.first > f.second) {
        dots.insert(Dot(2 * f.second - d.first, d.second));
        maxx = f.second;
      }
    }
  }
  std::ostringstream ss;
  for (unsigned long j = 0; j < maxy; ++j) {
    for (unsigned long i = 0; i < maxx; ++i) {
      ss << ((dots.find(Dot(i, j)) != dots.end()) ? "#" : ".");
    }
    ss << std::endl;
  }
  return ss.str();
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(p2(input));
}
