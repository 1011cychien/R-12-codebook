bool PIH(const vector<P> &h, P z, bool strict = true) {
  int n = (int)h.size(), a = 1, b = n - 1, r = !strict;
  if (n < 3) return r && isInter(Seg(h[0], h[n-1]), z);
  if (ori(h[0],h[a],h[b]) > 0) swap(a, b);
  if (ori(h[0],h[a],z) >= r || ori(h[0],h[b],z) <= -r)
    return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (ori(h[0], h[c], z) > 0 ? b : a) = c;
  }
  return ori(h[a], h[b], z) < r;
}
