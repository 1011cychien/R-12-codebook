template <typename U, typename V> struct min25 {
  lld n; int sq;
  vector<U> Ss, Sl, Spre; vector<V> Rs, Rl;
  Sieve sv; vector<lld> quo;
  U &S(lld d) { return d < sq ? Ss[d] : Sl[n / d]; }
  V &R(lld d) { return d < sq ? Rs[d] : Rl[n / d]; }
  min25(lld n_) : n(n_), sq((int)sqrt(n) + 1),
    Ss(sq), Sl(sq), Spre(sq), Rs(sq), Rl(sq), sv(sq) {
    for (lld i = 1, Q; i <= n; i = n / Q + 1)
      quo.push_back(Q = n / i);
  }
  U F_prime(auto &&f, auto &&F) {
    for (lld p : sv.primes) Spre[p] = f(p);
    for (int i = 1; i < sq; i++) Spre[i] += Spre[i - 1];
    for (lld i : quo) S(i) = F(i) - F(1);
    for (lld p : sv.primes)
      for (lld i : quo) {
        if (p * p > i) break;
        S(i) -= f(p) * (S(i / p) - Spre[p - 1]);
      }
    return S(n);
  } // F_prime: \sum _ {p is prime, p <= n} f(p)
  V F_comp(auto &&g) {
    for (lld i : quo) R(i) = V(S(i));
    for (lld p : sv.primes | views::reverse)
      for (lld i : quo) {
        if (p * p > i) break;
        lld prod = p;
        for (int c = 1; prod * p <= i; ++c, prod *= p) {
          R(i) += g(p, c) * (R(i / prod) - V(Spre[p]));
          R(i) += g(p, c + 1);
        }
      }
    return R(n);
  } // F_comp: \sum _ {2 <= i <= n} g(i)
};
/* U, V 都是環，記 h: U -> V 代表 U 轉型成 V 的函數。
要求 h(x + y) = h(x) + h(y)；f: lld -> U 是完全積性；
g 是積性函數且 h(f(p)) = g(p) 對於質數 p。
呼叫 F_comp 前需要先呼叫 F_prime 得到 S(i)。
S(i), R(i) 是 F_prime 和 F_comp 在 n/k 點的值。
F(i) = \sum _ {j <= i} f(j) 和 f(i) 需要快速求值。
g(p, c) := g(pow(p, c)) 需要快速求值。
例如若 g(p) 是度數 d 的多項式則可以構造 f(p) 是維護
pow(p, c) 的 (d+1)-tuple */
