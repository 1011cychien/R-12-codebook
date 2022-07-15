vector<Line>
tanline(const Circle &c1, const Circle &c2, int sign1){
  // sign1 = 1 for outer tang, -1 for inter tang
  vector<Line> ret;
  if (norm(c1.o - c2.o) < eps) return ret;
  llf d = abs(c1.o - c2.o);
  PTF v = (c2.o - c1.o) / d;
  llf c = (c1.r - sign1 * c2.r) / d;
  if (c * c > 1) return ret;
  llf h = sqrt(max<llf>(0, 1 - c * c));
  for (int sign2 : {1, -1}) {
    PTF n = c * v + sign2 * h * rot90(v);
    PTF p1 = c1.o + n * c1.r;
    PTF p2 = c2.o + n * (c2.r * sign1);
    if (norm(p2 - p1) < eps)
      p2 = p1 + rot90(c2.o - c1.o);
    ret.push_back({p1, p2});
  }
  return ret;
}
