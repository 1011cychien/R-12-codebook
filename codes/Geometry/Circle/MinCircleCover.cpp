Cir getCircum(P a, P b, P c){ // P = complex<llf>
  P z1 = a - b, z2 = a - c; llf D = cross(z1, z2) * 2;
  auto c1 = dot(a + b, z1), c2 = dot(a + c, z2);
  P o = rot90(c2 * z1 - c1 * z2) / D;
  return { o, abs(o - a) };
}
Cir minCircleCover(vector<P> p) { // what if p.empty?
  Cir c = { 0, 0 }; shuffle(all(p), mt19937(114514));
  for (size_t i = 0; i < p.size(); i++) {
    if (abs(p[i] - c.o) <= c.r) continue;
    c = { p[i], 0 };
    for (size_t j = 0; j < i; j++) {
      if (abs(p[j] - c.o) <= c.r) continue;
      c.o = (p[i] + p[j]) / llf(2);
      c.r = abs(p[i] - c.o);
      for (size_t k = 0; k < j; k++) {
        if (abs(p[k] - c.o) <= c.r) continue;
        c = getCircum(p[i], p[j], p[k]);
      }
    }
  }
  return c;
} // test @ TIOJ 1093 & luogu P1742
