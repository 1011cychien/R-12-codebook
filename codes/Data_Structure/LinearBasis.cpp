template <int BITS> struct Basis {
  array<pair<uint64_t, int>, BITS> b;
  Basis() { b.fill({0, -1}); }
  void add(uint64_t x, int p) {
    for (int i = 0; i < BITS; ++i) if ((x >> i) & 1) {
      if (b[i].first == 0) {
        b[i] = {x, p};
        return;
      } else if (b[i].second > p) {
        swap(b[i].first, x), swap(b[i].second, p);
      }
      x ^= b[i].first;
    }
  }
  bool ok(uint64_t x, int p) {
    for (int i = 0; i < BITS; ++i)
      if (((x >> i) & 1) and b[i].second < p)
        x ^= b[i].first;
    return x == 0;
  }
};
