struct Segment {
  PT st, dir; // represent st + t*dir for 0<=t<=1
  Segment(PT s, PT e) : st(s), dir(e - s) {}
  static bool valid(lld p, lld q) {
    // is there t s.t. 0 <= t <= 1 && qt == p ?
    if (q < 0) q = -q, p = -p;
    return 0 <= p && p <= q;
  }
};
bool isInter(Segment A, PT P) {
  if (A.dir == PT(0)) return P == A.st;
  return cross(P - A.st, A.dir) == 0 &&
    Segment::valid(dot(P - A.st, A.dir), norm(A.dir));
}
template <typename U, typename V>
bool isInter(U A, V B) {
  if (cross(A.dir, B.dir) == 0)
    return // handle parallel yourself
      isInter(A, B.st) || isInter(A, B.st+B.dir) ||
      isInter(B, A.st) || isInter(B, A.st+A.dir);
  PT D = B.st - A.st;
  lld C = cross(A.dir, B.dir);
  return U::valid(cross(D, B.dir), C) &&
      V::valid(cross(D, A.dir), C);
}
struct Line {
  PT st, ed, dir;
  Line (PT s, PT e)
    : st(s), ed(e), dir(e - s) {}
};
PTF intersect(const Line &A, const Line &B) {
  llf t = cross(B.st - A.st, B.dir) /
    llf(cross(A.dir, B.dir));
  return toPTF(A.st) + PTF(t) * toPTF(A.dir);
}
