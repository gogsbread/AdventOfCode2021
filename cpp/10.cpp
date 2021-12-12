
#include "common.h"

namespace {
std::map<char, char> braces{
    {')', '('}, {'(', ')'}, {'}', '{'}, {'{', '}'},
    {']', '['}, {'[', ']'}, {'>', '<'}, {'<', '>'},
};

long p1(const vs &input) {
  std::map<char, int> scores{
      {')', 3},
      {']', 57},
      {'}', 1197},
      {'>', 25137},
  };

  long score = 0;
  for (const std::string &s : input) {
    std::stack<char> st;
    for (const char &c : s) {
      if (st.empty()) {
        st.push(c);
        continue;
      }
      if (c == '(' || c == '[' || c == '{' || c == '<')
        st.push(c);
      else if (st.top() == braces[c])
        st.pop();
      else {
        score += scores[c];
        break;
      }
    }
  }
  return score;
}

long p2(const vs &input) {
  std::map<char, int> points{
      {')', 1},
      {']', 2},
      {'}', 3},
      {'>', 4},
  };

  std::vector<long> scores;
  for (const std::string &s : input) {
    std::deque<char> st;
    bool cor = false;
    for (const char &c : s) {
      if (st.empty()) {
        st.push_back(c);
        continue;
      }
      if (c == '(' || c == '[' || c == '{' || c == '<')
        st.push_back(c);
      else if (st.back() == braces[c])
        st.pop_back();
      else {
        cor = true;
        break;
      }
    }
    if (!cor && st.size() > 0) {
      long point = 0;
      for (auto it = st.rbegin(); it != st.rend(); std::advance(it, 1)) {
        point = point * 5 + points[braces[*it]];
      }
      scores.emplace_back(point);
    }
  }
  std::sort(scores.begin(), scores.end());
  return scores[scores.size() / 2];
}

} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}