template <int mod, int G, int maxn> struct NTT {
  static_assert (maxn == (maxn & -maxn));
  int roots[maxn];
  NTT () {
    int r = modpow(G, (mod - 1) / maxn);
    for (int i = maxn >> 1; i; i >>= 1) {
      roots[i] = 1;
      for (int j = 1; j < i; j++)
        roots[i + j] = mul(roots[i + j - 1], r);
      r = mul(r, r);
      // for (int j = 0; j < i; j++) // FFT (tested)
      //   roots[i+j] = polar<llf>(1, PI * j / i);
    }
  }
  // n must be 2^k, and 0 <= F[i] < mod
  template <typename T>
  void operator()(int F[], T n, bool inv = false) {
    for (T i = 0, j = 0; i < n; i++) {
      if (i < j) swap(F[i], F[j]);
      for (T k = n>>1; (j^=k) < k; k>>=1);
    }
    for (T s = 1; s < n; s *= 2) {
      for (T i = 0; i < n; i += s * 2) {
        for (T j = 0; j < s; j++) {
          int a = F[i+j], b = mul(F[i+j+s], roots[s+j]);
          F[i+j] = add(a, b);   // a + b
          F[i+j+s] = sub(a, b); // a - b
        }
      }
    }
    if (inv) {
      int iv = modinv(int(n));
      for (T i = 0; i < n; i++) F[i] = mul(F[i], iv);
      reverse(F + 1, F + n);
    }
  }
};
