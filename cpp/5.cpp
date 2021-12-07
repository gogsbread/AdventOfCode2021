#include "common.h"

namespace {
using Point = std::pair<int, int>;
using PointCloud = std::map<Point, int>;
PointCloud parse1(const vs &input) {
  PointCloud pc;
  for (const auto &l : input) {
    int x1, y1, x2, y2;
    std::sscanf(l.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
    if (x1 == x2) {
      const auto l = std::min(y1, y2);
      const auto u = std::max(y1, y2);
      for (int i = l; i <= u; ++i)
        pc[std::make_pair(x1, i)] += 1;
    } else if (y1 == y2) {
      const auto l = std::min(x1, x2);
      const auto u = std::max(x1, x2);
      for (int i = l; i <= u; ++i)
        pc[std::make_pair(i, y1)] += 1;
    }
  }
  return pc;
}

PointCloud parse2(const vs &input) {
  PointCloud pc;
  for (const auto &l : input) {
    int x1, y1, x2, y2;
    std::sscanf(l.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
    if (x1 == x2) {
      const auto l = std::min(y1, y2);
      const auto u = std::max(y1, y2);
      for (int i = l; i <= u; ++i)
        pc[std::make_pair(x1, i)] += 1;
    } else if (y1 == y2) {
      const auto l = std::min(x1, x2);
      const auto u = std::max(x1, x2);
      for (int i = l; i <= u; ++i)
        pc[std::make_pair(i, y1)] += 1;
    } else {
      auto l = std::make_pair(x1, y1);
      const auto u = std::make_pair(x2, y2);
      const int dx = (x1 < x2) ? 1 : -1;
      const int dy = (y1 < y2) ? 1 : -1;
      while (l != u) {
        pc[l] += 1;
        l = std::make_pair(l.first + dx, l.second + dy);
      }
      pc[u] += 1;
    }
  }
  return pc;
}

long p1(const vs &input) {
  PointCloud pc = parse1(input);
  return std::count_if(pc.begin(), pc.end(),
                       [](std::pair<Point, int> p) { return p.second >= 2; });
}

long p2(const vs &input) {
  PointCloud pc = parse2(input);
  return std::count_if(pc.begin(), pc.end(),
                       [](std::pair<Point, int> p) { return p.second >= 2; });
}

} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}