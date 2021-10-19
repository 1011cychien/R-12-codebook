using VL = vector<LL>;
#define fi(s, n) for (int i=int(s); i<int(n); ++i)
#define Fi(s, n) for (int i=int(n); i>int(s); --i)
int n2k(int n) {
  int sz = 1; while (sz < n) sz <<= 1;
  return sz;
}
template<int MAXN, LL P, LL RT> // MAXN = 2^k
struct Poly { // coefficients in [0, P)
  static NTT<MAXN, P, RT> ntt;
  VL coef;
  int n() const { return coef.size(); } // n()>=1
  LL *data() { return coef.data(); }
  const LL *data() const { return coef.data(); }
  LL &operator[](size_t i) { return coef[i]; }
  const LL &operator[](size_t i)const{return coef[i];}
  Poly(initializer_list<LL> a) : coef(a) { }
  explicit Poly(int _n = 1) : coef(_n) { }
  Poly(const LL *arr, int _n) : coef(arr, arr + _n) {}
  Poly(const Poly &p, int _n) : coef(_n) {
    copy_n(p.data(), min(p.n(), _n), data());
  }
  Poly& irev(){return reverse(data(),data()+n()),*this;}
  Poly& isz(int _n) { return coef.resize(_n), *this; }
  Poly& iadd(const Poly &rhs) { // n() == rhs.n()
    fi(0, n()) if ((coef[i]+=rhs[i]) >= P)coef[i]-=P;
    return *this;
  }
  Poly& imul(LL k) {
    fi(0, n()) coef[i] = coef[i] * k % P;
    return *this;
  }
  Poly Mul(const Poly &rhs) const {
    const int _n = n2k(n() + rhs.n() - 1);
    Poly X(*this, _n), Y(rhs, _n);
    ntt(X.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) X[i] = X[i] * Y[i] % P;
    ntt(X.data(), _n, true);
    return X.isz(n() + rhs.n() - 1);
  }
  Poly Inv() const { // coef[0] != 0
    if (n() == 1) return {ntt.minv(coef[0])};
    const int _n = n2k(n() * 2);
    Poly Xi = Poly(*this, (n() + 1)/2).Inv().isz(_n);
    Poly Y(*this, _n);
    ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) {
      Xi[i] *= (2 - Xi[i] * Y[i]) % P;
      if ((Xi[i] %= P) < 0) Xi[i] += P;
    }
    ntt(Xi.data(), _n, true);
    return Xi.isz(n());
  }
  Poly Sqrt() const { // Jacobi(coef[0], P) = 1
    if (n()==1) return {QuadraticResidue(coef[0], P)};
    Poly X = Poly(*this, (n()+1) / 2).Sqrt().isz(n());
    return X.iadd(Mul(X.Inv()).isz(n())).imul(P/2+1);
  }
  pair<Poly, Poly> DivMod(const Poly &rhs) const {
    // (rhs.)back() != 0
    if (n() < rhs.n()) return {{0}, *this};
    const int _n = n() - rhs.n() + 1;
    Poly X(rhs); X.irev().isz(_n);
    Poly Y(*this); Y.irev().isz(_n);
    Poly Q = Y.Mul(X.Inv()).isz(_n).irev();
    X = rhs.Mul(Q), Y = *this;
    fi(0, n()) if ((Y[i] -= X[i]) < 0) Y[i] += P;
    return {Q, Y.isz(max(1, rhs.n() - 1))};
  }
  Poly Dx() const {
    Poly ret(n() - 1);
    fi(0, ret.n()) ret[i] = (i + 1) * coef[i + 1] % P;
    return ret.isz(max(1, ret.n()));
  }
  Poly Sx() const {
    Poly ret(n() + 1);
    fi(0, n()) ret[i + 1]=ntt.minv(i + 1)*coef[i] % P;
    return ret;
  }
  Poly _tmul(int nn, const Poly &rhs) const {
    Poly Y = Mul(rhs).isz(n() + nn - 1);
    return Poly(Y.data() + n() - 1, nn);
  }
  VL _eval(const VL &x, const auto up)const{
    const int _n = (int)x.size();
    if (!_n) return {};
    vector<Poly> down(_n * 2);
    down[1] = DivMod(up[1]).second;
    fi(2,_n*2) down[i]=down[i/2].DivMod(up[i]).second;
    /* down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(_n, *this);
    fi(2, _n * 2) down[i] = up[i ^ 1]._tmul(up[i].n() - 1, down[i / 2]); */
    VL y(_n);
    fi(0, _n) y[i] = down[_n + i][0];
    return y;
  }
  static vector<Poly> _tree1(const VL &x) {
    const int _n = (int)x.size();
    vector<Poly> up(_n * 2);
    fi(0, _n) up[_n + i] = {(x[i] ? P - x[i] : 0), 1};
    Fi(0, _n-1) up[i] = up[i * 2].Mul(up[i * 2 + 1]);
    return up;
  }
  VL Eval(const VL&x)const{return _eval(x,_tree1(x));}
  static Poly Interpolate(const VL &x, const VL &y) {
    const int _n = (int)x.size();
    vector<Poly> up = _tree1(x), down(_n * 2);
    VL z = up[1].Dx()._eval(x, up);
    fi(0, _n) z[i] = y[i] * ntt.minv(z[i]) % P;
    fi(0, _n) down[_n + i] = {z[i]};
    Fi(0, _n-1) down[i]=down[i * 2].Mul(up[i * 2 + 1])
      .iadd(down[i * 2 + 1].Mul(up[i * 2]));
    return down[1];
  }
  Poly Ln() const { // coef[0] == 1
    return Dx().Mul(Inv()).Sx().isz(n());
  }
  Poly Exp() const { // coef[0] == 0
    if (n() == 1) return {1};
    Poly X = Poly(*this, (n() + 1)/2).Exp().isz(n());
    Poly Y = X.Ln(); Y[0] = P - 1;
    fi(0, n()) if((Y[i] = coef[i] - Y[i]) < 0)Y[i]+=P;
    return X.Mul(Y).isz(n());
  }
  Poly Pow(const string &K) const {
    int nz = 0;
    while (nz < n() && !coef[nz]) ++nz;
    LL nk = 0, nk2 = 0;
    for (char c : K) {
      nk = (nk * 10 + c - '0') % P;
      nk2 = nk2 * 10 + c - '0';
      if (nk2 * nz >= n()) return Poly(n());
      nk2 %= P - 1;
    }
    if (!nk && !nk2) return Poly({1}, n());
    Poly X(data() + nz, n() - nz * nk2);
    LL x0 = X[0];
    return X.imul(ntt.minv(x0)).Ln().imul(nk).Exp()
      .imul(ntt.mpow(x0, nk2)).irev().isz(n()).irev();
  }
  Poly InvMod(int L) { // (to evaluate linear recursion)
    Poly R{1, 0}; // *this * R mod x^L = 1 (*this[0] == 1)
    for (int level = 0; (1 << level) < L; ++level) {
      Poly O = R.Mul(Poly(data(), min(2 << level, n())));
      Poly Q(2 << level); Q[0] = 1;
      for (int j = (1 << level); j < (2 << level); ++j)
        Q[j] = (P - O[j]) % P;
      R = R.Mul(Q).isz(4 << level);
    }
    return R.isz(L);
  }
  static LL LinearRecursion(const VL&a,const VL&c,LL n){
    // a_n = \sum c_j a_(n-j)
    const int k = (int)a.size();
    assert((int)c.size() == k + 1);
    Poly C(k + 1), W({1}, k), M = {0, 1};
    fi(1, k + 1) C[k - i] = c[i] ? P - c[i] : 0;
    C[k] = 1;
    while (n) {
      if (n % 2) W = W.Mul(M).DivMod(C).second;
      n /= 2, M = M.Mul(M).DivMod(C).second;
    }
    LL ret = 0;
    fi(0, k) ret = (ret + W[i] * a[i]) % P;
    return ret;
  }
};
#undef fi
#undef Fi
using Poly_t = Poly<131072 * 2, 998244353, 3>;
template<> decltype(Poly_t::ntt) Poly_t::ntt = {};
