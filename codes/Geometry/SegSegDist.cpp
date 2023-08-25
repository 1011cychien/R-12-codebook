// be careful of abs<complex<int>> (replace _abs below)
llf PointSegDist(P A, Seg B) {
  if (B.dir == P(0)) return _abs(A - B.st);
  if (sgn(dot(A - B.st, B.dir)) *
      sgn(dot(A - B.ed, B.dir)) <= 0)
    return abs(cross(A - B.st, B.dir)) / _abs(B.dir);
  return min(_abs(A - B.st), _abs(A - B.ed));
}
llf SegSegDist(const Seg &s1, const Seg &s2) {
  if (isInter(s1, s2)) return 0;
  return min({
      PointSegDist(s1.st, s2),
      PointSegDist(s1.ed, s2),
      PointSegDist(s2.st, s1),
      PointSegDist(s2.ed, s1) });
} // test @ QOJ2444 / PTZ19 Summer.D3
