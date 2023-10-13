using Poly = vector<int>;
uint32_t n2k(uint32_t n) {
  if (n <= 1) return 1;
  return 1u << (32 - __builtin_clz(n - 1));
}
auto Mul(auto a, auto b, size_t sz) {
  a.resize(sz), b.resize(sz);
  ntt(a.data(), sz); ntt(b.data(), sz);
  fi(0, sz) a[i] = modmul(a[i], b[i]);
  return ntt(a.data(), sz, true), a;
}
Poly Newton(const Poly &v, auto &&init, auto &&iter) {
  Poly Q = { init(v[0]) };
  for (int sz = 2; Q.size() < v.size(); sz *= 2) {
    Poly A{v.begin(), v.begin() + min(sz, int(v.size()))};
    A.resize(sz * 2), Q.resize(sz * 2);
    iter(Q, A, sz * 2); Q.resize(sz);
  }
  return Q.resize(v.size()), Q;
}
Poly Inv(const Poly &v) { // v[0] != 0
  return Newton(v, modinv,
  [](Poly &X, Poly &A, int sz) {
    ntt(X.data(), sz), ntt(A.data(), sz);
    for (int i = 0; i < sz; i++)
      X[i] = modmul(X[i], modsub(2, modmul(X[i], A[i])));
    ntt(X.data(), sz, true);
  });
}
#define fi(l, r) for (size_t i = (l); i < (r); ++i)
Poly Dx(Poly A) {
  fi(1, A.size()) A[i - 1] = modmul(i, A[i]);
  return A.empty() ? A : (A.pop_back(), A);
}
Poly Sx(Poly A) {
  A.insert(A.begin(), 0);
  fi(1, A.size()) A[i] = modmul(modinv(i), A[i]);
  return A;
}
Poly Ln(const Poly &A) { // coef[0] == 1; res[0] == 0
  auto B = Sx(Mul(Dx(A), Inv(A), n2k(A.size() * 2)));
  return B.resize(A.size()), B;
}
Poly Exp(const Poly &v) { // coef[0] == 0; res[0] == 1
  return Newton(v, [](int x) { return 1; },
      [](Poly &X, Poly &A, int sz) {
        auto Y = X; Y.resize(sz / 2); Y = Ln(Y);
        fi(0, Y.size()) Y[i] = modsub(A[i], Y[i]);
        Y[0] = modadd(Y[0], 1); X = Mul(X, Y, sz);
      });
}
Poly Pow(Poly a, lld M) { // period mod*(mod-1)
  assert(!a.empty() && a[0] != 0);
  const int N = int(a.size()); // mod x^N
  const auto imul = [&a](int s) {
    for (int &x: a) x = modmul(x, s); }; int c = a[0];
  imul(modinv(c)); a = Ln(a); imul(M % mod);
  a = Exp(a); imul(modpow(c, M % (mod - 1)));
  return a;
}
Poly Sqrt(const Poly &v) { // need: QuadraticResidue
  assert(!v.empty() && v[0] != 0);
  const int r = get_root(v[0]); assert(r != -1);
  return Newton(u, [r](int x) { return r; },
    [](Poly &X, Poly &A, int sz) {
      auto Y = X; Y.resize(sz / 2);
      auto B = Mul(A, Inv(Y), sz);
      for (int i = 0; i < sz; i++)
        X[i] = modmul(mod / 2 + 1, modadd(X[i], B[i]));
    });
}
Poly Mul(auto &&a, auto &&b) {
  const int n = a.size() + b.size() - 1;
  auto R = Mul(a, b, n2k(n));
  return R.resize(n), R;
}
Poly MulT(Poly a, Poly b, int k) {
  assert(b.size()); reverse(all(b)); auto R = Mul(a, b);
  R = vector(R.begin() + b.size() - 1, R.end());
  return R.resize(k), R;
}
Poly Eval(const Poly &f, const Poly &x) {
  if (f.empty()) return vector(x.size(), 0);
  const int n = int(max(x.size(), f.size()));
  auto q = vector(n * 2, Poly(2, 1)); Poly ans(n);
  fi(0, x.size()) q[i + n][1] = modsub(0, x[i]);
  for (int i = n - 1; i > 0; i--)
    q[i] = Mul(q[i << 1], q[i << 1 | 1]);
  q[1] = MulT(f, Inv(q[1]), n);
  for (int i = 1; i < n; i++) {
    auto L = q[i << 1], R = q[i << 1 | 1];
    q[i << 1 | 0] = MulT(q[i], R, L.size());
    q[i << 1 | 1] = MulT(q[i], L, R.size());
  }
  for (int i = 0; i < n; i++) ans[i] = q[i + n][0];
  return ans.resize(x.size()), ans;
}
pair<Poly, Poly> DivMod(const Poly &A, const Poly &B) {
  assert(!B.empty() && B.back() != 0);
  if (A.size() < B.size()) return {{}, A};
  const int sz = A.size() - B.size() + 1;
  Poly X = B; reverse(all(X)); X.resize(sz);
  Poly Y = A; reverse(all(Y)); Y.resize(sz);
  Poly Q = Mul(Inv(X), Y);
  Q.resize(sz); reverse(all(Q)); X = Mul(Q, B); Y = A;
  fi(0, Y.size()) Y[i] = modsub(Y[i], X[i]);
  while (Y.size() && Y.back() == 0) Y.pop_back();
  while (Q.size() && Q.back() == 0) Q.pop_back();
  return {Q, Y};
} // empty means zero polynomial
int LinearRecursion(Poly a, Poly c, int64_t n) {
  const auto k = a.size(); assert(c.size() == k + 1);
  Poly p(k + 1), r(k), e = {0, 1}; r[0] = 1; p[k] = 1;
  fi(1, k + 1) p[k - i] = modsub(0, c[i]);
  for (; n; n >>= 1, e = DivMod(Mul(e, e), p).second)
    if (n & 1) r = DivMod(Mul(r, e), p).second;
  int ret = 0; r.resize(k);
  fi(0, k) ret = modadd(ret, modmul(r[i], a[i]));
  return ret;
} // a_n = \sum c_j a_(n-j), c_0 is not important
