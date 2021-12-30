
#include "common.h"

namespace {
struct Packet;
using Literal = unsigned long;
using Version = unsigned short;
using TypeId = unsigned short;
// you need to store raw pointers to express recursive types :(
using Packets = std::vector<Packet *>;
struct Operator {
  TypeId length_type_id;
  Packets packets;
};
struct Packet {
  Version version;
  TypeId type_id;
  std::variant<Literal, Operator> value;
};

std::string htob(const std::string &hex) {
  std::ostringstream bin;
  for (const char c : hex) {
    switch (std::toupper(c)) {
    case '0':
      bin << "0000";
      break;
    case '1':
      bin << "0001";
      break;
    case '2':
      bin << "0010";
      break;
    case '3':
      bin << "0011";
      break;
    case '4':
      bin << "0100";
      break;
    case '5':
      bin << "0101";
      break;
    case '6':
      bin << "0110";
      break;
    case '7':
      bin << "0111";
      break;
    case '8':
      bin << "1000";
      break;
    case '9':
      bin << "1001";
      break;
    case 'A':
      bin << "1010";
      break;
    case 'B':
      bin << "1011";
      break;
    case 'C':
      bin << "1100";
      break;
    case 'D':
      bin << "1101";
      break;
    case 'E':
      bin << "1110";
      break;
    case 'F':
      bin << "1111";
      break;
    default:
      break;
    }
  }
  return bin.str();
}

template <typename T>
T btod(const std::string &bin, const size_t &st, const size_t &len) {
  T d = 0;
  const auto start = std::next(bin.begin(), st);
  const auto end = std::next(start, len);
  for (auto it = start; it != end; ++it) {
    d <<= 1;
    d |= (*it == '1') ? 1 : 0;
  }
  return d;
}

std::pair<size_t, Packet> decode(const std::string &b, const size_t &st) {
  size_t end = st;
  Packet p;
  p.version = btod<Version>(b, st, 3);
  p.type_id = btod<TypeId>(b, st + 3, 3);
  if (p.type_id == 4) {
    Literal lit = 0;
    constexpr size_t offset = 5;
    bool last = false;
    for (size_t i = 0; !last; ++i) {
      last = (btod<unsigned short>(b, st + 6 + i * offset, 1) == 0);
      lit <<= 4;
      lit |= btod<Literal>(b, st + 7 + i * offset, 4);
      end = (st + 7 + i * offset) + 4;
    }
    p.value = lit;
  } else {
    Operator op;
    op.length_type_id = btod<TypeId>(b, st + 6, 1);
    if (op.length_type_id == 1) {
      Packets pkts;
      size_t last = st + 18;
      for (size_t n = btod<size_t>(b, st + 7, 11); n > 0; --n) {
        const auto &out = decode(b, last);
        pkts.emplace_back(new Packet(out.second));
        last = out.first;
      }
      op.packets = std::move(pkts);
      end = last;
    } else {
      Packets pkts;
      size_t n = btod<size_t>(b, st + 7, 15);
      size_t last = st + 22;
      while (n > 0) {
        const auto &out = decode(b, last);
        pkts.emplace_back(new Packet(out.second));
        n -= (out.first - last);
        last = out.first;
      }
      op.packets = std::move(pkts);
      end = last;
    }
    p.value = op;
  }
  return std::make_pair(end, p);
}

Packet parse(const std::string &b) {
  const auto &[_, p] = decode(b, 0);
  return p;
}

long p1(const std::string &input) {
  const std::string b = htob(input);
  Packet p = parse(b);
  std::deque<Packet> pkts{p};
  long vs = 0;
  while (!pkts.empty()) {
    const Packet &pkt = pkts.front();
    vs += pkt.version;
    if (std::holds_alternative<Operator>(pkt.value)) {
      const auto &op = std::get<Operator>(pkt.value);
      for (const auto &p : op.packets) {
        pkts.push_back(*p);
      }
    }
    pkts.pop_front();
  }
  return vs;
}

long value(const Packet &pkt) {
  if (pkt.type_id == 4)
    return std::get<Literal>(pkt.value);

  if (pkt.type_id == 0) {
    long r = 0;
    for (const auto &p : std::get<Operator>(pkt.value).packets) {
      r += value(*p);
    }
    return r;
  }

  if (pkt.type_id == 1) {
    long r = 1;
    for (const auto &p : std::get<Operator>(pkt.value).packets) {
      r *= value(*p);
    }
    return r;
  }

  if (pkt.type_id == 2) {
    long r = LONG_MAX;
    for (const auto &p : std::get<Operator>(pkt.value).packets) {
      r = std::min(r, value(*p));
    }
    return r;
  }

  if (pkt.type_id == 3) {
    long r = LONG_MIN;
    for (const auto &p : std::get<Operator>(pkt.value).packets) {
      r = std::max(r, value(*p));
    }
    return r;
  }

  if (pkt.type_id == 5) {
    const auto &p1 = value(*(std::get<Operator>(pkt.value).packets[0]));
    const auto &p2 = value(*(std::get<Operator>(pkt.value).packets[1]));
    return p1 > p2;
  }

  if (pkt.type_id == 6) {
    const auto &p1 = value(*(std::get<Operator>(pkt.value).packets[0]));
    const auto &p2 = value(*(std::get<Operator>(pkt.value).packets[1]));
    return p1 < p2;
  }

  if (pkt.type_id == 7) {
    const auto &p1 = value(*(std::get<Operator>(pkt.value).packets[0]));
    const auto &p2 = value(*(std::get<Operator>(pkt.value).packets[1]));
    return p1 == p2;
  }

  return 0;
}

long p2(const std::string &input) {
  const std::string b = htob(input);
  Packet p = parse(b);
  return value(p);
}

} // namespace

int main() {
  const auto input = gb::advent2020::readIn();
  gb::advent2020::writeOut(std::to_string(p1(input[0])));
  gb::advent2020::writeOut(std::to_string(p2(input[0])));
}