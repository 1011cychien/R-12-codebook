struct FastMod {
  using Big = __uint128_t; llu b, m;
  FastMod(llu b) : b(b), m(-1ULL / b) {}
  llu reduce(llu a) { // a % b
    llu r = a - (llu)((Big(m) * a) >> 64) * b;
    return r >= b ? r - b : r;
  }
};
