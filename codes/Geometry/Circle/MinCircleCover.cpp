// be careful of type
Cir getCircum(P a, P b, P c){
  P z1 = a - b, z2 = a - c; llf D = cross(z1, z2) * 2;
  llf c1 = dot(a + b, z1), c2 = dot(a + c, z2);
  P o = (c2 * conj(z1) - c1 * conj(z2)) / D;
  return { o, abs(o - a) };
}
Cir minCircleCover(vector<P> &pts) {
  shuffle(pts.begin(), pts.end(), mt19937(114514));
  Cir c = { pts[0], 0 };
  for(int i = 0; i < (int)pts.size(); i++) {
    if (dist(pts[i], c.o) <= c.r) continue;
    c = { pts[i], 0 };
    for (int j = 0; j < i; j++) {
      if (dist(pts[j], c.o) <= c.r) continue;
      c.o = (pts[i] + pts[j]) / llf(2);
      c.r = dist(pts[i], c.o);
      for (int k = 0; k < j; k++) {
        if (dist(pts[k], c.o) <= c.r) continue;
        c = getCircum(pts[i], pts[j], pts[k]);
      }
    }
  }
  return c;
}
