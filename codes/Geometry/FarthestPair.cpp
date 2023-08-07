// stk is from convex hull
int n = (int)(stk.size()), pos = 1; lld ans = 0;
for (int i = 0; i < n; i++) {
  P e = stk[(i + 1) % n] - stk[i];
  while (abs(cross(e, stk[(pos + 1) % n] - stk[i])) >
         abs(cross(e, stk[pos] - stk[i])))
    pos = (pos + 1) % n;
  for (int j: {i, i + 1})
    ans = max(ans, norm(stk[pos] - stk[j]));
}
