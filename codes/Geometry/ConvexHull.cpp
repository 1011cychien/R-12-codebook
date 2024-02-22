// from NaCl, counterclockwise, be careful of n<=2
vector<P> convex_hull(vector<P> v) { // n==0 will RE
  sort(all(v)); // by X then Y
  if (v[0] == v.back()) return {v[0]};
  int t = 0, s = 1; vector<P> h(v.size() + 1);
  for (int _ = 2; _--; s = t--, reverse(all(v)))
    for (P p : v) {
      while (t>s && ori(p, h[t-1], h[t-2]) >= 0) t--;
      h[t++] = p;
    }
  return h.resize(t), h;
}
