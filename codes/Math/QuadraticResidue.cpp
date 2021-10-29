struct S {
  int MOD, w;
  int64_t x, y;
  S(int m, int w_=-1, int64_t x_=1, int64_t y_=0)
    : MOD(m), w(w_), x(x_), y(y_) {}
  S operator*(const S &rhs) const {
    int w_ = w;
    if (w_ == -1) w_ = rhs.w;
    assert(w_ != -1 and w_ == rhs.w);
    return { MOD, w_,
      (x * rhs.x + y * rhs.y % MOD * w) % MOD,
      (x * rhs.y + y * rhs.x) % MOD };
  }
};
int64_t get_root(int64_t n, int P) {
  if (P == 2) return 1;
  auto check = [&](int64_t x) {
    return qpow(x, (P - 1) / 2, P); };
  if (check(n) == P-1) return -1;
  int64_t a; int w; mt19937 rnd(7122);
  do { a = rnd() % P;
    w = ((a * a - n) % P + P) % P;
  } while (check(w) != P-1);
  return qpow(S(P, w, a, 1), (P + 1) / 2).x;
}
