#include "common.h"

namespace {
using Board = std::array<std::array<std::string, 5>, 5>;
using BoardState = std::array<std::array<bool, 5>, 5>;
using BoardWinnings = std::array<std::array<int, 5>, 2>;

vs splitoncomma(const std::string &s) {
  std::istringstream ss(s);
  vs ts;
  for (std::string p; std::getline(ss, p, ',');) {
    ts.emplace_back(p);
  }
  return ts;
}

vs splitonspace(const std::string &s) {
  std::istringstream ss(s);
  vs ts;
  std::string p;
  while (ss >> p) {
    ts.emplace_back(p);
  }
  return ts;
}

auto parse(const vs &input) {
  const auto nums = splitoncomma(input[0]);

  std::unordered_map<std::string, std::vector<std::tuple<int, size_t, size_t>>>
      boardindex;
  std::unordered_map<int, Board> boards{};
  std::unordered_map<int, BoardState> boardstates{};
  int b = -1;
  for (size_t i = 1, r = 0; i < input.size(); ++i, ++r) {
    if ((i - 1) % 6 == 0) {
      ++b;
      r = -1;
      continue;
    }

    const auto row = splitonspace(input[i]);
    for (size_t c = 0; c < row.size(); ++c) {
      boards[b][r][c] = row[c];
      boardstates[b][r][c] = false;
      boardindex[row[c]].emplace_back(std::make_tuple(b, r, c));
    };
  }
  return std::make_tuple(nums, boards, boardstates, boardindex);
}

long p1(const vs &input) {
  auto [nums, boards, boardstates, boardindex] = parse(input);

  // bingo
  std::unordered_map<int, BoardWinnings> boardwinnings{};
  for (const auto &num : nums) {
    for (const auto &bi : boardindex[num]) {
      auto &[b, r, c] = bi;

      auto &[row, col] = boardwinnings[b];
      row[r] += 1;
      col[c] += 1;

      boardstates[b][r][c] = true;
      if (row[r] == 5 || col[c] == 5) {
        long sum = 0;
        for (size_t i = 0; i < 5; ++i) {
          for (size_t j = 0; j < 5; ++j) {
            if (!boardstates[b][i][j]) {
              sum += std::stol(boards[b][i][j]);
            }
          }
        }
        return std::stol(num) * sum;
      }
    }
  }
  return 0;
}

long p2(const vs &input) {
  auto [nums, boards, boardstates, boardindex] = parse(input);

  // bingo
  std::unordered_map<int, BoardWinnings> boardwinnings{};
  std::vector<std::pair<int, std::string>> winners{};
  for (const auto &num : nums) {
    for (const auto &bi : boardindex[num]) {
      auto &[b, r, c] = bi;

      auto &[row, col] = boardwinnings[b];
      row[r] += 1;
      col[c] += 1;

      const auto &result = std::find_if(
          winners.begin(), winners.end(),
          [&b](std::pair<int, std::string> p) { return p.first == b; });
      if (result == winners.end())
        boardstates[b][r][c] = true;
      if (row[r] == 5 || col[c] == 5) {
        if (result == winners.end()) {
          winners.emplace_back(std::make_pair(b, num));
        }
      };
    }
  }
  long sum = 0;
  const auto &[b, num] = *(--winners.end());
  for (size_t i = 0; i < 5; ++i) {
    for (size_t j = 0; j < 5; ++j) {
      if (!boardstates[b][i][j]) {
        sum += std::stol(boards[b][i][j]);
      }
    }
  }
  return std::stol(num) * sum;
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}