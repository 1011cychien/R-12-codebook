template <typename T>
auto euclid(lld a, lld b, lld c, lld n, T U, T R) {
  b %= c;
  if (a >= c)
    return euclid(a % c, b, c, n, U, mpow(U, a / c) * R);
  lld m = (i128(a) * n + b) / c;
  if (!m) return mpow(R, n);
  return mpow(R, (c - b - 1) / a) * U *
                euclid(c, c - b - 1, a, m - 1, R, U) *
                mpow(R, n - (i128(c) * m - b - 1) / a);
}
// time complexity is O(log max(a, c))
// 給定二維座標系上的一次函數 $y = (ax + b) / c$
// 維護一個矩陣 $A = I$，考慮 $x \in [0, n)$
// 每次向右穿過網格的垂直線時，乘上一個矩陣 $R$
// 每次向上穿過網格的水平線時，乘上一個矩陣 $U$
// 若剛好經過一個整點，那麼先乘 $U$ 再乘 $R$
