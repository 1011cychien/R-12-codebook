struct Line {
  lld a, b, c; // ax + by + c <= 0
  P dir() const { return P(a, b); }
  Line(lld ta, lld tb, lld tc) : a(ta), b(tb), c(tc) {}
  Line(P S, P T):a(IM(T-S)),b(-RE(T-S)),c(cross(T,S)) {}
}; using LN = const Line &;
PF intersect(LN A, LN B) {
  llf c = cross(A.dir(), B.dir());
  i128 a = i128(A.c) * B.a - i128(B.c) * A.a;
  i128 b = i128(A.c) * B.b - i128(B.c) * A.b;
  return PF(-b / c, a / c);
}
bool cov(LN l, LN A, LN B) {
  i128 c = cross(A.dir(), B.dir());
  i128 a = i128(A.c) * B.a - i128(B.c) * A.a;
  i128 b = i128(A.c) * B.b - i128(B.c) * A.b;
  return sgn(a * l.b - b * l.a + c * l.c) * sgn(c) >= 0;
}
bool operator<(LN a, LN b) {
  if (int c = argCmp(a.dir(), b.dir())) return c == -1;
  return i128(abs(b.a) + abs(b.b)) * a.c >
                  i128(abs(a.a) + abs(a.b)) * b.c;
}
