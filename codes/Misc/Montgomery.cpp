struct Mont { // Montegomery multiplication
  constexpr static int W = 64;
  llu mod, R1Mod, R2Mod, NPrime;
  void set_mod(llu _mod) {
    mod = _mod; assert(mod & 1);
    const u128 B = u128(1) << W, R = B % mod;
    llu xinv = 1;
    for (int i = 1; i < W; i++) // Hensel lifting
      if ((xinv * mod) >> i & 1) xinv |= 1ULL << i;
    assert(xinv * mod == 1);
    R1Mod = static_cast<llu>(R);
    R2Mod = static_cast<llu>(R * R % mod);
    NPrime = static_cast<llu>(B - xinv);
  }
  llu redc(llu a, llu b) const {
    auto T = static_cast<u128>(a) * b;
    u128 m = static_cast<llu>(T) * NPrime;
    T += m * mod; T >>= W;
    return static_cast<llu>(T >= mod ? T - mod : T);
  }
  llu from(llu x) const {
    assert(x < mod);
    return redc(x, R2Mod);
  }
  llu get(llu a) const { return redc(a, 1); }
  llu one() const { return R1Mod; }
} mont;
// a * b % mod == get(redc(from(a), from(b)))
