// find_first = l -> minimal x s.t. check( [l, x) )
// find_last = r -> maximal x s.t. check( [x, r) )
int find_first(int l, auto &&check) {
  if (l >= n) return n + 1;
  l += sz; push(l); Monoid sum; // identity
  do {
    while ((l & 1) == 0) l >>= 1;
    if (auto s = sum + nd[l]; check(s)) {
      while (l < sz) {
        prop(l); l = (l << 1);
        if (auto nxt = sum + nd[l]; not check(nxt))
          sum = nxt, l++;
      }
      return l + 1 - sz;
    } else sum = s, l++;
  } while (lowbit(l) != l);
  return n + 1;
}
int find_last(int r, auto &&check) {
  if (r <= 0) return -1;
  r += sz; push(r - 1); Monoid sum; // identity
  do {
    r--;
    while (r > 1 and (r & 1)) r >>= 1;
    if (auto s = nd[r] + sum; check(s)) {
      while (r < sz) {
        prop(r); r = (r << 1) | 1;
        if (auto nxt = nd[r] + sum; not check(nxt))
          sum = nxt, r--;
      }
      return r - sz;
    } else sum = s;
  } while (lowbit(r) != r);
  return -1;
}
