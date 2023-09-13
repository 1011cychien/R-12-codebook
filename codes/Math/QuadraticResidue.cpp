struct S {
  int MOD, w;
  int64_t x, y;
  S(int m, int w_=-1, int64_t x_=1, int64_t y_=0)
    : MOD(m), w(w_), x(x_), y(y_) {}
  S operator*(const S &rhs) const {
    return { MOD, rhs.w,
      (x * rhs.x + y * rhs.y % MOD * rhs.w) % MOD,
      (x * rhs.y + y * rhs.x) % MOD };
  }
};
int get_root(int n, int P) {
	if (P == 2 or n == 0) return n;
  auto check = [&](int x) {
		return qpow(x, (P - 1) / 2, P); };
	if (check(n) != 1) return -1;
	int64_t a; int w; mt19937 rnd(7122);
	do { a = rnd() % P;
		w = ((a * a - n) % P + P) % P;
	} while (check(w) != P - 1);
	return qpow(S(P, w, a, 1), (P + 1) / 2).x;
}
