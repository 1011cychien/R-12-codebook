struct Mont { // Montgomery multiplication
  constexpr static int W = 64, L = 6;
  llu mod, R1, R2, xinv;
  void set_mod(llu _mod) {
    mod = _mod; assert(mod & 1); xinv = 1;
    for (int j = 0; j < L; j++) xinv *= 2 - xinv * mod;
    assert(xinv * mod == 1);
    const u128 R = (u128(1) << W) % mod;
    R1 = llu(R); R2 = llu(R*R % mod);
  }
  llu redc(llu a, llu b) const {
    u128 T = u128(a) * b, m = -llu(T) * xinv;
    T += m * mod; T >>= W;
    return llu(T >= mod ? T - mod : T);
  }
  llu from(llu x) const {
    assert(x < mod); return redc(x, R2); }
  llu get(llu a) const { return redc(a, 1); }
  llu one() const { return R1; }
} mont;
// a * b % mod == get(redc(from(a), from(b)))
