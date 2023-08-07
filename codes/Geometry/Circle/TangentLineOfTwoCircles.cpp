// be careful of tangent / exact same circle
// sign1 = 1 for outer tang, -1 for inter tang
vector<Line> common_tan(const Cir &a, const Cir &b, int sign1) {
  if (norm(a.o - b.o) < eps) return {};
  llf d = abs(a.o - b.o), c = (a.r - sign1 * b.r) / d;
  PTF v = (b.o - a.o) / d;
  if (c * c > 1) return {};
  if (abs(c * c - 1) < eps) {
    PTF p = a.o + c * v * a.r;
    return {Line(p, p + rot90(b.o - a.o))};
  }
  vector<Line> ret; llf h = sqrt(max(0.0l, 1-c*c));
  for (int sign2 : {1, -1}) {
    PTF n = c * v + sign2 * h * rot90(v);
    PTF p1 = a.o + n * a.r;
    PTF p2 = b.o + n * (b.r * sign1);
    ret.emplace_back(p1, p2);
  }
  return ret;
}
