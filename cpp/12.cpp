
#include "common.h"

namespace {
using Node = std::string;
using Path = std::vector<Node>;
using Graph = std::map<Node, std::vector<Node>>;

Graph parse(const vs &input) {
  Graph g{};
  for (auto const &s : input) {
    std::istringstream ss(s);
    Node s1, s2;
    std::getline(ss, s1, '-');
    std::getline(ss, s2);
    g[s1].emplace_back(s2);
    g[s2].emplace_back(s1);
  }
  return g;
}

bool is_small(Node n) {
  for (const char &c : n) {
    if (int(c) < 97 || int(c) > 122)
      return false;
  }
  return true;
}

long p1(const vs &input) {
  Graph g = parse(input);

  long paths = 0;
  std::deque<Path> q;
  Path p{"start"};
  q.emplace_back(p);
  while (q.size() > 0) {
    auto path = q.back();
    q.pop_back();
    const Node &u = *path.rbegin();
    if (u == "end") {
      paths += 1;
      continue;
    }
    for (const Node &v : g[u]) {
      if ((is_small(v) &&
           std::find(path.begin(), path.end(), v) == path.end()) ||
          !is_small(v)) {
        Path p{path};
        p.emplace_back(v);
        q.emplace_back(p);
      }
    }
  }

  return paths;
}

long p2(const vs &input) {

  auto reuse_small_path = [](Path p) {
    Path small_paths;
    std::copy_if(p.begin(), p.end(),
                 std::inserter(small_paths, small_paths.begin()),
                 [](Node n) { return is_small(n); });
    const std::set<Node> s_small_paths(small_paths.begin(), small_paths.end());
    return small_paths.size() == s_small_paths.size();
  };

  Graph g = parse(input);

  long paths = 0;
  std::deque<Path> q;
  Path p{"start"};
  q.emplace_back(p);
  while (q.size() > 0) {
    auto path = q.back();
    q.pop_back();
    const Node &u = *path.rbegin();
    if (u == "end") {
      paths += 1;
      continue;
    }
    for (const Node &v : g[u]) {
      if ((is_small(v) &&
           std::find(path.begin(), path.end(), v) == path.end()) ||
          (is_small(v) && v != "start" && reuse_small_path(path)) ||
          !is_small(v)) {
        Path p{path};
        p.emplace_back(v);
        q.emplace_back(p);
      }
    }
  }

  return paths;
}
} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}