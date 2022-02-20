bool CCinter(Cir &a, Cir &b, pdd &p1, pdd &p2) {
  pdd o1 = a.o, o2 = b.o;
  double r1 = a.r, r2 = b.r, d2 = abs2(o1 - o2),
         d = sqrt(d2);
  if(d < max(r1, r2) - min(r1, r2) || d > r1 + r2)
    return 0;
  pdd u = (o1 + o2) * 0.5
    + (o1 - o2) * ((r2 * r2 - r1 * r1) / (2 * d2));
  double A = sqrt((r1 + r2 + d) * (r1 - r2 + d)
          * (r1 + r2 - d) * (-r1 + r2 + d));
  pdd v = rot90(o2 - o1) * A / (2 * d2);
  p1 = u + v, p2 = u - v;
  return 1;
}
