
#include "common.h"

namespace {
using Grid = std::array<std::array<int, 10>, 10>;

Grid parse(const vs &input) {
  Grid g{};
  size_t i = 0;
  for (const auto &s : input) {
    size_t j = 0;
    for (const auto &c : s) {
      g[i][j] = std::stoi(std::string(1, c));
      ++j;
    }
    ++i;
  }
  return g;
}

std::array<int, 8> dx{-1, 0, 1, -1, 1, -1, 0, 1};
std::array<int, 8> dy{-1, -1, -1, 0, 0, 1, 1, 1};

long p1(const vs &input, size_t turns) {
  Grid g = parse(input);
  long t = 0;
  for (size_t _ = 0; _ < turns; ++_) {
    std::deque<std::pair<size_t, size_t>> flashing;
    std::set<std::pair<size_t, size_t>> flashed;
    for (size_t i = 0; i < g.size(); ++i) {
      for (size_t j = 0; j < g[0].size(); ++j) {
        g[i][j] += 1;
        if (g[i][j] > 9) {
          t += 1;
          flashing.emplace_back(std::make_pair(i, j));
          flashed.insert(std::make_pair(i, j));
        }
      }
    }

    while (flashing.size() > 0) {
      const auto [y, x] = flashing.back();
      g[y][x] = 0;
      flashing.pop_back();
      for (size_t i = 0; i < dx.size(); ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        const auto p = std::make_pair(ny, nx);
        if (nx >= 0 && ny >= 0 && nx < (int)g[0].size() && ny < (int)g.size() &&
            (flashed.find(p) == flashed.end())) {
          g[ny][nx] += 1;
          if (g[ny][nx] > 9) {
            t += 1;
            flashing.emplace_back(p);
            flashed.insert(p);
          }
        }
      }
    }
  }
  return t;
}

long p2(const vs &input, size_t turns) {
  Grid g = parse(input);
  for (size_t t = 0; t < turns; ++t) {
    std::deque<std::pair<size_t, size_t>> flashing;
    std::set<std::pair<size_t, size_t>> flashed;
    for (size_t i = 0; i < g.size(); ++i) {
      for (size_t j = 0; j < g[0].size(); ++j) {
        g[i][j] += 1;
        if (g[i][j] > 9) {
          flashing.emplace_back(std::make_pair(i, j));
          flashed.insert(std::make_pair(i, j));
        }
      }
    }

    while (flashing.size() > 0) {
      const auto [y, x] = flashing.back();
      g[y][x] = 0;
      flashing.pop_back();
      for (size_t i = 0; i < dx.size(); ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        const auto p = std::make_pair(ny, nx);
        if (nx >= 0 && ny >= 0 && nx < (int)g[0].size() && ny < (int)g.size() &&
            (flashed.find(p) == flashed.end())) {
          g[ny][nx] += 1;
          if (g[ny][nx] > 9) {
            flashing.emplace_back(p);
            flashed.insert(p);
          }
        }
      }
    }

    if (flashed.size() == 100) {
      return t + 1;
    }
  }

  return -1;
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input, 100)));
  gb::advent2020::writeOut(std::to_string(p2(input, 1000)));
}