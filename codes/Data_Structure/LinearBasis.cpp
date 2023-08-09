template <int BITS, typename S = int> struct Basis {
  static constexpr S MIN = numeric_limits<S>::min();
  array<pair<llu, S>, BITS> b;
  Basis() { b.fill({0, MIN}); }
  void add(llu x, S p) {
    for (int i = BITS-1; i>=0; i--) if (x >> i & 1) {
      if (b[i].first == 0) return b[i]={x, p}, void();
      if (b[i].second < p)
        swap(b[i].first, x), swap(b[i].second, p);
      x ^= b[i].first;
    }
  }
  optional<llu> query_kth(llu v, llu k) {
    vector<pair<llu, int>> o;
    for (int i = 0; i < BITS; i++)
      if (b[i].first) o.emplace_back(b[i].first, i);
    if (k >= (1ULL << o.size())) return {};
    for (int i = int(o.size()) - 1; i >= 0; i--)
      if ((k >> i & 1) ^ (v >> o[i].second & 1))
        v ^= o[i].first;
    return v;
  }
  Basis filter(S l) {
    Basis res = *this;
    for (int i = 0; i < BITS; i++)
      if (res.b[i].second < l) res.b[i] = {0, MIN};
    return res;
  }
};
