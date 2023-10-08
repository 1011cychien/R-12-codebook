// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b)/m) mod 2^64
llu floor_sum_unsigned(llu n, llu m, llu a, llu b) {
  llu ans = 0;
  while (true) {
    if (a >= m) ans += n*(n-1)/2 * (a/m), a %= m;
    if (b >= m) ans += n * (b/m), b %= m;
    if (llu y_max = a * n + b; y_max >= m) {
      n = (llu)(y_max / m), b = (llu)(y_max % m);
      swap(m, a);
    } else break;
  }
  return ans;
}
lld floor_sum(lld n, lld m, lld a, lld b) {
  llu ans = 0;
  if (a < 0) {
    llu a2 = (a % m + m), d = (a2 - a) / m;
    ans -= 1ULL * n * (n - 1) / 2 * d; a = a2;
  }
  if (b < 0) {
    llu b2 = (b % m + m), d = (b2 - b) / m;
    ans -= 1ULL * n * d; b = b2;
  }
  return ans + floor_sum_unsigned(n, m, a, b);
}
