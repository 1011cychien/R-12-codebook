struct L {
  mutable lld a, b, p;
  bool operator<(const L &r) const {
    return a < r.a; /* here */ }
  bool operator<(lld x) const { return p < x; }
};
lld Div(lld a, lld b) {
  return a / b - ((a ^ b) < 0 && a % b); }
struct DynamicHull : multiset<L, less<>> {
  static const lld kInf = 1e18;
  bool Isect(iterator x, iterator y) {
    if (y == end()) { x->p = kInf; return false; }
    if (x->a == y->a)
      x->p = x->b > y->b ? kInf : -kInf; /* here */
    else x->p = Div(y->b - x->b, x->a - y->a);
    return x->p >= y->p;
  }
  void Insert(lld a, lld b) {
    auto z = insert({a, b, 0}), y = z++, x = y;
    while (Isect(y, z)) z = erase(z);
    if (x!=begin()&&Isect(--x,y)) Isect(x, y=erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      Isect(x, erase(y));
  }
  lld Query(lld x) {   // default chmax
    auto l = *lower_bound(x);  // to chmin:
    return l.a * x + l.b;      // modify the 2 "<>"
  }
};
