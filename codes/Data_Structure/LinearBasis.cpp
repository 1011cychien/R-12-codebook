template <int BITS>
struct LinearBasis {
  array<uint64_t, BITS> basis;
  Basis() { basis.fill(0); } 
  void add(uint64_t x) {
    for (int i = 0; i < BITS; ++i) if ((x >> i) & 1) {
      if (basis[i] == 0) {
        basis[i] = x;
        return;
      }
      x ^= basis[i];
    }
  }
  bool ok(uint64_t x) {
    for (int i = 0; i < BITS; ++i)
      if ((x >> i) & 1) x ^= basis[i];
    return x == 0;
  }
};
