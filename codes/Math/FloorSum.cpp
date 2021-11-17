// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b)/m) mod 2^64
llu floor_sum_unsigned(llu n, llu m, llu a, llu b) {
  llu ans = 0;
  while (true) {
    if (a >= m) {
      ans += n * (n - 1) / 2 * (a / m); a %= m;
    }
    if (b >= m) {
      ans += n * (b / m); b %= m;
    }
    llu y_max = a * n + b;
    if (y_max < m) break;
    // y_max < m * (n + 1)
    // floor(y_max / m) <= n
    n = (llu)(y_max / m), b = (llu)(y_max % m);
    swap(m, a);
  }
  return ans;
}
lld floor_sum(lld n, lld m, lld a, lld b) {
  llu ans = 0;
  if (a < 0) {
    llu a2 = (a % m + m) % m;
    ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
    a = a2;
  }
  if (b < 0) {
    llu b2 = (b % m + m) % m;
    ans -= 1ULL * n * ((b2 - b) / m);
    b = b2;
  }
  return ans + floor_sum_unsigned(n, m, a, b);
}
