#define fi(l, r) for (size_t i = (l); i < (r); ++i)
using S = vector<int>;
auto Mul(auto a, auto b, size_t sz) {
  a.resize(sz), b.resize(sz);
  ntt(a.data(), sz); ntt(b.data(), sz);
  fi(0, sz) a[i] = mul(a[i], b[i]);
  return ntt(a.data(), sz, true), a;
}
S Newton(const S &v, int init, auto &&iter) {
  S Q = { init };
  for (int sz = 2; Q.size() < v.size(); sz *= 2) {
    S A{begin(v), begin(v) + min(sz, int(v.size()))};
    A.resize(sz * 2), Q.resize(sz * 2);
    iter(Q, A, sz * 2); Q.resize(sz);
  }
  return Q.resize(v.size()), Q;
}
S Inv(const S &v) { // v[0] != 0
  return Newton(v, modinv(v[0]),
    [](S &X, S &A, int sz) {
      ntt(X.data(), sz), ntt(A.data(), sz);
      for (int i = 0; i < sz; i++)
        X[i] = mul(X[i], sub(2, mul(X[i], A[i])));
      ntt(X.data(), sz, true); });
}
S Dx(S A) {
  fi(1, A.size()) A[i - 1] = mul(i, A[i]);
  return A.empty() ? A : (A.pop_back(), A);
}
S Sx(S A) {
  A.insert(A.begin(), 0);
  fi(1, A.size()) A[i] = mul(modinv(int(i)), A[i]);
  return A;
}
S Ln(const S &A) { // coef[0] == 1; res[0] == 0
  auto B = Sx(Mul(Dx(A), Inv(A), bit_ceil(A.size()*2)));
  return B.resize(A.size()), B;
}
S Exp(const S &v) { // coef[0] == 0; res[0] == 1
  return Newton(v, 1,
    [](S &X, S &A, int sz) {
      auto Y = X; Y.resize(sz / 2); Y = Ln(Y);
      fi(0, Y.size()) Y[i] = sub(A[i], Y[i]);
      Y[0] = add(Y[0], 1); X = Mul(X, Y, sz); });
}
S Pow(S a, lld M) { // period mod*(mod-1)
  assert(!a.empty() && a[0] != 0);
  const auto imul = [&a](int s) {
    for (int &x: a) x = mul(x, s); }; int c = a[0];
  imul(modinv(c)); a = Ln(a); imul(int(M % mod));
  a = Exp(a); imul(modpow(c, int(M % (mod - 1))));
  return a; // mod x^N where N=a.size()
}
S Sqrt(const S &v) { // need: QuadraticResidue
  assert(!v.empty() && v[0] != 0);
  const int r = get_root(v[0]); assert(r != -1);
  return Newton(v, r,
    [](S &X, S &A, int sz) {
      auto Y = X; Y.resize(sz / 2);
      auto B = Mul(A, Inv(Y), sz);
      for (int i = 0, inv2 = mod / 2 + 1; i < sz; i++)
        X[i] = mul(inv2, add(X[i], B[i])); });
}
S Mul(auto &&a, auto &&b) {
  const auto n = a.size() + b.size() - 1;
  auto R = Mul(a, b, bit_ceil(n));
  return R.resize(n), R;
}
S MulT(S a, S b, size_t k) {
  assert(b.size()); reverse(all(b)); auto R = Mul(a, b);
  R = vector(R.begin() + b.size() - 1, R.end());
  return R.resize(k), R;
}
S Eval(const S &f, const S &x) {
  if (f.empty()) return vector(x.size(), 0);
  const int n = int(max(x.size(), f.size()));
  auto q = vector(n * 2, S(2, 1)); S ans(n);
  fi(0, x.size()) q[i + n][1] = sub(0, x[i]);
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
pair<S, S> DivMod(const S &A, const S &B) {
  assert(!B.empty() && B.back() != 0);
  if (A.size() < B.size()) return {{}, A};
  const auto sz = A.size() - B.size() + 1;
  S X = B; reverse(all(X)); X.resize(sz);
  S Y = A; reverse(all(Y)); Y.resize(sz);
  S Q = Mul(Inv(X), Y);
  Q.resize(sz); reverse(all(Q)); X = Mul(Q, B); Y = A;
  fi(0, Y.size()) Y[i] = sub(Y[i], X[i]);
  while (Y.size() && Y.back() == 0) Y.pop_back();
  while (Q.size() && Q.back() == 0) Q.pop_back();
  return {Q, Y};
} // empty means zero polynomial
int LinearRecursionKth(S a, S c, int64_t k) {
  const auto d = a.size(); assert(c.size() == d + 1);
  const auto sz = bit_ceil(2 * d + 1), o = sz / 2;
  S q = c; for (int &x: q) x = sub(0, x); q[0]=1;
  S p = Mul(a, q); p.resize(sz); q.resize(sz);
  for (int r; r = (k & 1), k; k >>= 1) {
    fill(d + all(p), 0); fill(d + 1 + all(q), 0);
    ntt(p.data(), sz); ntt(q.data(), sz);
    for (size_t i = 0; i < sz; i++)
      p[i] = mul(p[i], q[(i + o) & (sz - 1)]);
    for (size_t i = 0, j = o; j < sz; i++, j++)
      q[i] = q[j] = mul(q[i], q[j]);
    ntt(p.data(), sz, true); ntt(q.data(), sz, true);
    for (size_t i = 0; i < d; i++) p[i] = p[i << 1 | r];
    for (size_t i = 0; i <= d; i++) q[i] = q[i << 1];
  } // Bostan-Mori
  return mul(p[0], modinv(q[0]));
} // a_n = \sum c_j a_(n-j), c_0 is not used
