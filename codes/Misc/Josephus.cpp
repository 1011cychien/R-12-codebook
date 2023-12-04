lld f(lld n, lld m, lld k) { // n people kill m for each turn
  lld s = (m - 1) % (n - k); // O(k)
  for (lld i = n - k + 1; i <= n; i++) s = (s + m) % i;
  return s;
}
lld kth(lld n, lld m, i128 k) { // died at kth
  if (m == 1) return k;         // O(m log(n))
  for (k = k*m+m-1; k >= n; k = k-n + (k-n)/(m-1));
  return k;
} // k and result are 0-based, test @ CF 101955
