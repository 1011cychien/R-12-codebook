bool PIH(const vector<P> &l, P p, bool strict = true) {
  int n = l.size(), a = 1, b = n - 1, r = !strict;
  if (n < 3) return r && isInter(Seg(l[0], l[n-1]), p);
  if (ori(l[0],l[a],l[b]) > 0) swap(a, b);
  if (ori(l[0],l[a],p) >= r || ori(l[0],l[b],p) <= -r)
    return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (ori(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return ori(l[a], l[b], p) < r;
}
