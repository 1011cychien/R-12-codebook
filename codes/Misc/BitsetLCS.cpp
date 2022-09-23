scanf("%d%d", &n, &m), u = n / 64 + 1;
for (int i = 1, c; i <= n; i++)
  scanf("%d", &c), p[c].set(i);
for (int i = 1, c; i <= m; i++) {
  scanf("%d", &c), (g = f) |= p[c];
  f.shift(), f.set(0);
  ((f = g - f) ^= g) &= g;
}
printf("%d\n", f.count());
