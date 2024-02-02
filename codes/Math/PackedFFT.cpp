VL convolution(const VI &a, const VI &b) {
  if (a.empty() || b.empty()) return {};
  const int sz = bit_ceil(a.size() + b.size() - 1);
  // Should be able to handle N <= 10^5, C <= 10^4
  vector<P> v(sz);
  for (size_t i = 0; i < a.size(); ++i) v[i].RE(a[i]);
  for (size_t i = 0; i < b.size(); ++i) v[i].IM(b[i]);
  fft(v.data(), sz, /*inv=*/false);
  auto rev = v; reverse(1 + all(rev));
  for (int i = 0; i < sz; ++i) {
    P A = (v[i] + conj(rev[i])) / P(2, 0);
    P B = (v[i] - conj(rev[i])) / P(0, 2);
    v[i] = A * B;
  }
  VL c(sz); fft(v.data(), sz, /*inv=*/true);
  for (int i = 0; i < sz; ++i) c[i] = roundl(RE(v[i]));
  return c;
}
VI convolution_mod(const VI &a, const VI &b) {
  if (a.empty() || b.empty()) return {};
  const int sz = bit_ceil(a.size() + b.size() - 1);
  vector<P> fa(sz), fb(sz);
  for (size_t i = 0; i < a.size(); ++i)
    fa[i] = P(a[i] & ((1 << 15) - 1), a[i] >> 15);
  for (size_t i = 0; i < b.size(); ++i)
    fb[i] = P(b[i] & ((1 << 15) - 1), b[i] >> 15);
  fft(fa.data(), sz); fft(fb.data(), sz);
  auto rfa = fa; reverse(1 + all(rfa));
  for (int i = 0; i < sz; ++i) fa[i] *= fb[i];
  for (int i = 0; i < sz; ++i) fb[i] *= conj(rfa[i]);
  fft(fa.data(), sz, true); fft(fb.data(), sz, true);
  vector<int> res(sz);
  for (int i = 0; i < sz; ++i) {
    lld A = (lld)roundl(RE((fa[i] + fb[i]) / P(2, 0)));
    lld C = (lld)roundl(IM((fa[i] - fb[i]) / P(0, 2)));
    lld B = (lld)roundl(IM(fa[i])); B %= p; C %= p;
    res[i] = (A + (B << 15) + (C << 30)) % p;
  }
  return res;
} // test @ yosupo judge with long double
