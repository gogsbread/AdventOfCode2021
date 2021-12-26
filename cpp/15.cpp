
#include "common.h"

namespace {
using Weight = unsigned short;
using Vertex = std::pair<long, long>;

// ya iterator is an overkill but just want to do it
class AdjIterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = Vertex;

public:
  AdjIterator(const Vertex &v = Vertex(-1, -1), const size_t m = 0,
              const size_t n = 0)
      : _v(v), _m(m), _n(n) {
    ++(*this);
  }

  const Vertex &operator*() const { return _v; }
  const std::unique_ptr<Vertex> operator->() const {
    return std::make_unique<Vertex>(_v);
  }
  AdjIterator &operator++() {
    auto t =
        Vertex(_v.first + (-1 * _dx[_i - 1]), _v.second + (-1 * _dy[_i - 1]));
    for (; _i < _dx.size(); ++_i) {
      auto x = t.first + _dx[_i];
      auto y = t.second + _dy[_i];
      if (x >= 0 && y >= 0 && x < (long)_m && y < (long)_n) {
        ++_i;
        _v = Vertex(x, y);
        return *this;
      }
    }

    _v = Vertex(-1, -1);
    return *this;
  }
  AdjIterator operator++(int) {
    AdjIterator t(*this);
    ++(*this);
    return t;
  }
  friend bool operator==(const AdjIterator &a, const AdjIterator &b) {
    return a._v == b._v;
  }
  friend bool operator!=(const AdjIterator &a, const AdjIterator &b) {
    return a._v != b._v;
  }

private:
  Vertex _v;
  size_t _m;
  size_t _n;

  unsigned int _i = 1;
  std::array<int, 5> _dx{0, -1, 1, 0, 0};
  std::array<int, 5> _dy{0, 0, 0, -1, 1};
};

class AdjMatrix {
public:
  size_t m = 0, n = 0;

public:
  explicit AdjMatrix(const vs &input) {
    _mat = {};
    for (const auto &s : input) {
      std::vector<Weight> r;
      for (const char c : s) {
        r.emplace_back(c - '0');
      }
      _mat.emplace_back(r);
    }
    n = _mat[0].size();
    m = _mat.size();
  }
  Weight at(const Vertex &u) { return _mat[u.second][u.first]; }
  AdjIterator adj_begin(Vertex u) { return AdjIterator(u, m, n); }
  AdjIterator adj_end() { return AdjIterator(); }

private:
  std::vector<std::vector<Weight>> _mat;
};

long djikstra(AdjMatrix m) {
  std::map<Vertex, long> risks;
  for (size_t j = 0; j < m.m; ++j) {
    for (size_t i = 0; i < m.n; ++i) {
      risks[Vertex(i, j)] = LONG_MAX;
    }
  }
  risks[Vertex(0, 0)] = 0;
  std::set<Vertex> explored;
  std::set<std::pair<Weight, Vertex>> unexplored{
      std::make_pair(risks[Vertex(0, 0)], Vertex(0, 0))};
  while (!unexplored.empty()) {
    const auto &it = unexplored.begin();
    const auto &[w, u] = *it;
    for (auto it = m.adj_begin(u); it != m.adj_end(); ++it) {
      const auto &v = *it;
      if (explored.find(v) == explored.end() && (m.at(v) + w) < risks.at(v)) {
        risks[v] = m.at(v) + w;
        unexplored.insert(std::make_pair(risks[v], v));
      }
    }
    explored.insert(u);
    unexplored.erase(it);
  }
  return risks[Vertex(m.n - 1, m.m - 1)];
}

long p1(const vs &input) {
  auto m = AdjMatrix(input);
  return djikstra(m);
}

long p2(const vs &input) {
  size_t m = input.size();
  size_t n = input[0].size();
  vs t(m * 5, std::string(n * 5, '0'));
  for (size_t j = 0; j < 5 * m; ++j) {
    for (size_t i = 0; i < 5 * n; ++i) {
      t[j][i] =
          ((input[j % m][i % n] + (i / n) + (j / m) - '1') % ('9' - '0')) + '1';
    }
  }
  auto mat = AdjMatrix(t);
  return djikstra(mat);
}

} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input)));
  gb::advent2020::writeOut(std::to_string(p2(input)));
}