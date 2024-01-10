struct S { int rough; lld large; int id; };
lld PrimeCount(lld n) { // n ~ 10^13 => < 1s
  if (n <= 1) return 0;
  const int v = static_cast<int>(sqrtl(n)); int pc = 0;
  vector<int> smalls(v + 1), skip(v + 1); vector<S> z;
  for (int i = 2; i <= v; ++i) smalls[i] = (i + 1) / 2;
  for (int i : views::iota(0, (v + 1) / 2))
    z.emplace_back(2*i+1, (n / (2*i+1) + 1) / 2, i);
  for (int p = 3; p <= v; ++p)
    if (smalls[p] > smalls[p - 1]) {
    const int q = p * p; ++pc;
    if (1LL * q * q > n) break;
    skip[p] = 1;
    for (int i = q; i <= v; i += 2 * p) skip[i] = 1;
    int ns = 0;
    for (auto e : z) if (!skip[e.rough]) {
      lld d = 1LL * e.rough * p;
      e.large += pc - (d <= v ? z[smalls[d] - pc].large : smalls[n / d]);
      e.id = ns; z[ns++] = e;
    }
    z.resize(ns);
    for (int j = v / p; j >= p; --j) {
      int c = smalls[j] - pc, e = min(j * p + p, v + 1);
      for (int i = j * p; i < e; ++i) smalls[i] -= c;
    }
  }
  lld ans = z[0].large; z.erase(z.begin());
  for (auto &[rough, large, k] : z) {
    const lld m = n / rough; --k;
    ans -= large - (pc + k);
    for (auto [p, _, l] : z)
      if (l >= k || p * p > m) break;
      else ans += smalls[m / p] - (pc + l);
  }
  return ans;
} // test @ yosupo library checker w/ n=1e11, 68ms
