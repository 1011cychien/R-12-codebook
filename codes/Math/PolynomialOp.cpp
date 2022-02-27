using V = vector<int>;
#define fi(s, n) for (int i = int(s); i < int(n); ++i)
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
  Poly &isz(int _n) { return resize(_n), *this; }
  Poly &iadd(const Poly &rhs) { // n() == rhs.n()
    fi(0, size())(*this)[i] = modadd((*this)[i], rhs[i]);
    return *this;
  }
  Poly &imul(int k) {
    fi(0, size())(*this)[i] = modmul((*this)[i], k);
    return *this;
  }
  Poly Mul(const Poly &rhs) const {
    const int _n = n2k(size() + rhs.size() - 1);
    Poly X(*this, _n), Y(rhs, _n);
    ntt(X.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) X[i] = modmul(X[i], Y[i]);
    ntt(X.data(), _n, true);
    return X.isz(size() + rhs.size() - 1);
  }
  Poly Inv() const { // coef[0] != 0
    if (size() == 1) return V{modinv(*begin())};
    const int _n = n2k(size() * 2);
    Poly Xi = Poly(*this, (size() + 1) / 2).Inv().isz(_n), Y(*this, _n);
    ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) Xi[i] = modmul(Xi[i], modsub(2, modmul(Xi[i], Y[i])));
    ntt(Xi.data(), _n, true);
    return Xi.isz(size());
  }
  Poly Sqrt() const { // coef[0] \in [1, mod)^2
    if (size() == 1) return V{QuadraticResidue((*this)[0], mod)};
    Poly X = Poly(*this, (size() + 1) / 2).Sqrt().isz(size());
    return X.iadd(Mul(X.Inv()).isz(size())).imul(mod / 2 + 1);
  }
  pair<Poly, Poly> DivMod(const Poly &rhs) const {
    if (size() < rhs.size()) return {V{0}, *this};
    const int _n = size() - rhs.size() + 1;
    Poly X(rhs); X.irev().isz(_n);
    Poly Y(*this); Y.irev().isz(_n);
    Poly Q = Y.Mul(X.Inv()).isz(_n).irev();
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
  Poly _tmul(int nn, const Poly &rhs) const {
    Poly Y = Mul(rhs).isz(size() + nn - 1);
    return V(Y.data() + size() - 1, Y.data() + Y.size());
  }
  V _eval(const V &x, const vector<Poly> &up) const {
    const int _n = (int)x.size();
    if (!_n) return {};
    vector<Poly> down(_n * 2);
    // down[1] = DivMod(up[1]).second;
    // fi(2, _n * 2) down[i] = down[i / 2].DivMod(up[i]).second;
    down[1] = Poly(up[1]).irev().isz(size()).Inv().irev()._tmul(_n, *this);
    fi(2, _n * 2) down[i] = up[i ^ 1]._tmul(up[i].size() - 1, down[i / 2]);
    V y(_n); fi(0, _n) y[i] = down[_n + i][0];
    return y;
  }
  static vector<Poly> _tree1(const V &x) {
    const int _n = (int)x.size();
    vector<Poly> up(_n * 2);
    fi(0, _n) up[_n + i] = V{modsub(mod, x[i]), 1};
    for(int i=_n-1;i>0;--i) up[i] = up[i * 2].Mul(up[i * 2 + 1]);
    return up;
  }
  V Eval(const V &x) const { return _eval(x, _tree1(x)); }
  static Poly Interpolate(const V &x, const V &y) {
    const int _n = (int)x.size();
    vector<Poly> up = _tree1(x), down(_n * 2);
    V z = up[1].Dx()._eval(x, up);
    fi(0, _n) z[i] = modmul(y[i], modinv(z[i]));
    fi(0, _n) down[_n + i] = V{z[i]};
    for(int i=_n-1;i>0;--i) down[i] = down[i * 2].Mul(up[i * 2 + 1]).iadd(down[i * 2 + 1].Mul(up[i * 2]));
    return down[1];
  }
  Poly Ln() const { // coef[0] == 1
    return Dx().Mul(Inv()).Sx().isz(size());
  }
  Poly Exp() const { // coef[0] == 0
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
  Poly InvMod(int L) { // (to evaluate linear recursion)
    Poly R{1, 0}; // *this * R mod x^L = 1 (*this[0] == 1)
    for (int level = 0; (1 << level) < L; ++level) {
      Poly O = R.Mul(Poly(data(), min<int>(2 << level, size())));
      Poly Q(2 << level); Q[0] = 1;
      for (int j = (1 << level); j < (2 << level); ++j)
        Q[j] = modsub(mod, O[j]);
      R = R.Mul(Q).isz(4 << level);
    }
    return R.isz(L);
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
