// be careful of type
Cir getCircum(P a, P b, P c){
  llf a1 = a.x-b.x, b1 = a.y-b.y;
  llf c1 = (a.x+b.x)/2 * a1 + (a.y+b.y)/2 * b1;
  llf a2 = a.x-c.x, b2 = a.y-c.y;
  llf c2 = (a.x+c.x)/2 * a2 + (a.y+c.y)/2 * b2;
  Cir cc;
  cc.o.x = (c1*b2-b1*c2)/(a1*b2-b1*a2);
  cc.o.y = (a1*c2-c1*a2)/(a1*b2-b1*a2);
  cc.r = hypot(cc.o.x-a.x, cc.o.y-a.y);
  return cc;
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
