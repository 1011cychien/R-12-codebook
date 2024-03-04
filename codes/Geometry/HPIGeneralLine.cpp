struct Line {
  lld a, b, c; // ax + by + c <= 0
  P dir() const { return P(a, b); }
}; using LN = const Line &;
PF intersect(LN A, LN B) {
  P x(A.a, B.a), y(A.b, B.b), z(A.c, B.c);
  llf D = cross(x, y);
  return PF(cross(y, z) / D, cross(z, x) / D);
}
bool cov(LN l, LN A, LN B) {
  P x(A.a, B.a), y(A.b, B.b), z(A.c, B.c);
  i128 c = cross(x,y), a = cross(y,z), b = cross(z,x);
  return sgn(a * l.a + b * l.b + c * l.c) * sgn(c) > 0;
}
bool operator<(LN a, LN b) {
  if (int c = argCmp(a.dir(), b.dir())) return c == -1;
  return a.c > b.c;
}
