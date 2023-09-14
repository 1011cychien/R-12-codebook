struct Seg { // closed segment
  P st, dir; // represent st + t*dir for 0<=t<=1
  Seg(P s, P e) : st(s), dir(e - s) {}
  static bool valid(lld p, lld q) {
    // is there t s.t. 0 <= t <= 1 && qt == p ?
    if (q < 0) q = -q, p = -p;
    return 0 <= p && p <= q;
  }
  vector<P> ends() const { return { st, st + dir }; }
};
template <typename T> bool isInter(T A, P p) {
  if (A.dir == P(0)) return p == A.st; // BE CAREFUL
  return cross(p - A.st, A.dir) == 0 &&
    T::valid(dot(p - A.st, A.dir), norm(A.dir));
}
template <typename U, typename V>
bool isInter(U A, V B) {
  if (cross(A.dir, B.dir) == 0) { // BE CAREFUL
    bool res = false;
    for (P p: A.ends()) res |= isInter(B, p);
    for (P p: B.ends()) res |= isInter(A, p);
    return res;
  }
  P D = B.st - A.st; lld C = cross(A.dir, B.dir);
  return U::valid(cross(D, B.dir), C) &&
    V::valid(cross(D, A.dir), C);
}
