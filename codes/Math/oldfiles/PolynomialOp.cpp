using V = vector<int>;
#define fi(l, r) for (int i = int(l); i < int(r); ++i)
template <int mod, int G, int maxn> struct Poly : V {
  static uint32_t n2k(uint32_t n) {
    if (n <= 1) return 1;
    return 1u << (32 - __builtin_clz(n - 1));
  }
  static NTT<mod,G,maxn> ntt; // coefficients in [0, P)
  explicit Poly(int n = 1) : V(n) {}
  Poly(const V &v) : V(v) {}
  Poly(const Poly &p, size_t n) : V(n) {
    copy_n(p.data(), min(p.size(), n), data());
  }
  Poly &irev() { return reverse(data(), data() + size()), *this; }
  Poly &isz(int sz) { return resize(sz), *this; }
  Poly &iadd(const Poly &rhs) { // n() == rhs.n()
    fi(0, size())(*this)[i] = modadd((*this)[i], rhs[i]);
    return *this;
  }
  Poly &imul(int k) {
    fi(0, size())(*this)[i] = modmul((*this)[i], k);
    return *this;
  }
  Poly Mul(const Poly &rhs) const {
    const int sz = n2k(size() + rhs.size() - 1);
    Poly X(*this, sz), Y(rhs, sz);
    ntt(X.data(), sz), ntt(Y.data(), sz);
    fi(0, sz) X[i] = modmul(X[i], Y[i]);
    ntt(X.data(), sz, true);
    return X.isz(size() + rhs.size() - 1);
  }
  Poly Inv() const { // coef[0] != 0
    if (size() == 1) return V{modinv(*begin())};
    const int sz = n2k(size() * 2);
    Poly X = Poly(*this, (size() + 1) / 2).Inv().isz(sz), Y(*this, sz);
    ntt(X.data(), sz), ntt(Y.data(), sz);
    fi(0, sz) X[i] = modmul(X[i], modsub(2, modmul(X[i], Y[i])));
    ntt(X.data(), sz, true);
    return X.isz(size());
  }
  Poly Sqrt() const { // coef[0] \in [1, mod)^2
    if (size() == 1) return V{QuadraticResidue((*this)[0], mod)};
    Poly X = Poly(*this, (size() + 1) / 2).Sqrt().isz(size());
    return X.iadd(Mul(X.Inv()).isz(size())).imul(mod / 2 + 1);
  }
  pair<Poly, Poly> DivMod(const Poly &rhs) const {
    if (size() < rhs.size()) return {V{0}, *this};
    const int sz = size() - rhs.size() + 1;
    Poly X(rhs); X.irev().isz(sz);
    Poly Y(*this); Y.irev().isz(sz);
    Poly Q = Y.Mul(X.Inv()).isz(sz).irev();
    X = rhs.Mul(Q), Y = *this;
    fi(0, size()) Y[i] = modsub(Y[i], X[i]);
    return {Q, Y.isz(max<int>(1, rhs.size() - 1))};
  }
  Poly Dx() const {
    Poly ret(size() - 1);
    fi(0, ret.size()) ret[i] = modmul(i + 1, (*this)[i + 1]);
    return ret.isz(max<int>(1, ret.size()));
  }
  Poly Sx() const {
    Poly ret(size() + 1);
    fi(0, size()) ret[i + 1] = modmul(modinv(i + 1), (*this)[i]);
    return ret;
  }
  Poly Ln() const { // coef[0] == 1; res[0] == 0
    return Dx().Mul(Inv()).Sx().isz(size());
  }
  Poly Exp() const { // coef[0] == 0; res[0] == 1
    if (size() == 1) return V{1};
    Poly X = Poly(*this, (size() + 1) / 2).Exp().isz(size());
    Poly Y = X.Ln(); Y[0] = mod - 1;
    fi(0, size()) Y[i] = modsub((*this)[i], Y[i]);
    return X.Mul(Y).isz(size());
  }
  Poly Pow(const string &K) const {
    int nz = 0;
    while (nz < size() && !(*this)[nz]) ++nz;
    int nk = 0, nk2 = 0;
    for (char c : K) {
      nk = (nk * 10 + c - '0') % mod;
      nk2 = nk2 * 10 + c - '0';
      if (nk2 * nz >= size())
        return Poly(size());
      nk2 %= mod - 1;
    }
    if (!nk && !nk2) return Poly(V{1}, size());
    Poly X = V(data() + nz, data() + size() - nz * (nk2 - 1));
    int x0 = X[0];
    return X.imul(modinv(x0)).Ln().imul(nk).Exp().imul(modpow(x0, nk2)).irev().isz(size()).irev();
  }
  V Eval(V x) const {
    if (x.empty()) return {};
    const size_t n = max(x.size(), size());
    vector<Poly> t(n * 2, V{1, 0}), f(n * 2);
    for (size_t i = 0; i < x.size(); ++i)
      t[n + i] = V{1, mod-x[i]};
    for (size_t i = n - 1; i > 0; --i)
      t[i] = t[i * 2].Mul(t[i * 2 + 1]);
    f[1] = Poly(*this, n).irev().Mul(t[1].Inv()).isz(n).irev();
    for (size_t i = 1; i < n; ++i) {
      auto o = f[i]; auto sz = o.size();
      f[i*2] = o.irev().Mul(t[i*2+1]).isz(sz).irev().isz(t[i*2].size());
      f[i*2+1] = o.Mul(t[i*2]).isz(sz).irev().isz(t[i*2+1].size());
    }
    for (size_t i=0;i<x.size();++i) x[i] = f[n+i][0];
    return x;
  }

  static int LinearRecursion(const V &a, const V &c, int64_t n) { // a_n = \sum c_j a_(n-j)
    const int k = (int)a.size();
    assert((int)c.size() == k + 1);
    Poly C(k + 1), W({1}, k), M = {0, 1};
    fi(1, k + 1) C[k - i] = modsub(mod, c[i]);
    C[k] = 1;
    while (n) {
      if (n % 2) W = W.Mul(M).DivMod(C).second;
      n /= 2, M = M.Mul(M).DivMod(C).second;
    }
    int ret = 0;
    fi(0, k) ret = modadd(ret, modmul(W[i], a[i]));
    return ret;
  }
};
#undef fi
using Poly_t = Poly<998244353, 3, 1 << 20>;
template <> decltype(Poly_t::ntt) Poly_t::ntt = {};
