Cir getCircum(P a, P b, P c){ // P = complex<llf>
  P z1 = a - b, z2 = a - c; llf D = cross(z1, z2) * 2;
  llf c1 = dot(a + b, z1), c2 = dot(a + c, z2);
  P o = rot90(c2 * z1 - c1 * z2) / D;
  return { o, abs(o - a) };
}
Cir minCircleCover(vector<P> pts) {
  assert (!pts.empty());
  ranges::shuffle(pts, mt19937(114514));
  Cir c = { 0, 0 };
  for(size_t i = 0; i < pts.size(); i++) {
    if (abs(pts[i] - c.o) <= c.r) continue;
    c = { pts[i], 0 };
    for (size_t j = 0; j < i; j++) {
      if (abs(pts[j] - c.o) <= c.r) continue;
      c.o = (pts[i] + pts[j]) / llf(2);
      c.r = abs(pts[i] - c.o);
      for (size_t k = 0; k < j; k++) {
        if (abs(pts[k] - c.o) <= c.r) continue;
        c = getCircum(pts[i], pts[j], pts[k]);
      }
    }
  }
  return c;
} // test @ TIOJ 1093 & luogu P1742
