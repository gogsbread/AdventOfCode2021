#include "common.h"

namespace {
std::vector<std::vector<int>> parse(const vs &input) {
  std::vector<std::vector<int>> r;
  for (const auto &s : input) {
    std::vector<int> t;
    for (const char &c : s) {
      t.emplace_back(std::stoi(std::string(1, c)));
    }
    r.emplace_back(t);
  }
  return r;
}

long p1(const vs &input) {
  const auto tubes = parse(input);
  std::array<int, 4> dx = {-1, 0, 1, 0};
  std::array<int, 4> dy = {0, -1, 0, 1};
  long r = 0;
  for (size_t i = 0; i < tubes.size(); ++i) {
    for (size_t j = 0; j < tubes[0].size(); ++j) {
      bool b = true;
      for (size_t k = 0; k < 4; ++k) {
        int x = j + dx[k], y = i + dy[k];
        if (x >= 0 && y >= 0 && y < (int)tubes.size() &&
            x < (int)tubes[0].size())
          b = b && (tubes[i][j] < tubes[y][x]);
      }
      if (b) {
        r += (tubes[i][j] + 1);
      }
    }
  }
  return r;
}

long p2(const vs &input) {
  const auto tubes = parse(input);
  std::array<int, 4> dx = {-1, 0, 1, 0};
  std::array<int, 4> dy = {0, -1, 0, 1};
  std::set<std::pair<int, int>> vb;
  std::vector<int> basins;
  for (size_t i = 0; i < tubes.size(); ++i) {
    for (size_t j = 0; j < tubes[0].size(); ++j) {
      if (tubes[i][j] != 9 && vb.find(std::make_pair(i, j)) == vb.end()) {
        std::stack<std::pair<int, int>> st;
        st.push(std::make_pair(i, j));
        vb.insert(std::make_pair(i, j));
        int basin = 0;
        while (st.size() > 0) {
          const auto [y, x] = st.top();
          st.pop();
          ++basin;
          for (size_t k = 0; k < 4; ++k) {
            int a = x + dx[k], b = y + dy[k];
            if (a >= 0 && b >= 0 && a < (int)tubes[0].size() &&
                b < (int)tubes.size() &&
                vb.find(std::make_pair(b, a)) == vb.end() && tubes[b][a] != 9) {
              st.push(std::make_pair(b, a));
              vb.insert(std::make_pair(b, a));
            }
          }
        }
        basins.emplace_back(basin);
      }
    }
  }
  std::sort(basins.begin(), basins.end(), std::greater());
  return (long)basins[0] * (long)basins[1] * (long)basins[2];
}

} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}