// find_first = x -> minimal x s.t. check( [a, x) )
// find_last = x -> maximal x s.t. check( [x, b) )
template <typename C>
int find_first(int l, const C &check) {
  if (l >= n) return n;
  l += sz;
  for (int i = height; i > 0; i--)
    propagate(l >> i);
  Monoid sum = identity;
  do {
    while ((l & 1) == 0) l >>= 1;
    if (check(f(sum, data[l]))) {
      while (l < sz) {
        propagate(l);
        l <<= 1;
        auto nxt = f(sum, data[l]);
        if (not check(nxt)) {
          sum = nxt;
          l++;
        }
      }
      return l + 1 - sz;
    }
    sum = f(sum, data[l++]);
  } while ((l & -l) != l);
  return n;
}
template <typename C>
int find_last(int r, const C &check) {
  if (r <= 0) return -1;
  r += sz;
  for (int i = height; i > 0; i--)
    propagate((r - 1) >> i);
  Monoid sum = identity;
  do {
    r--;
    while (r > 1 and (r & 1)) r >>= 1;
    if (check(f(data[r], sum))) {
      while (r < sz) {
        propagate(r);
        r = (r << 1) + 1;
        auto nxt = f(data[r], sum);
        if (not check(nxt)) {
          sum = nxt;
          r--;
        }
      }
      return r - sz;
    }
    sum = f(data[r], sum);
  } while ((r & -r) != r);
  return -1;
}
