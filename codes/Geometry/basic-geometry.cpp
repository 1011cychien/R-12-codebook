#define IM imag
#define RE real
using lld = int64_t;
using llf = long double;
using Point = std::complex<lld>;
using Pointf = std::complex<llf>;
auto toPointf(Point p) {
  return Pointf{IM(p), RE(p)};
}
int sgn(lld x) {
  return (x > 0) - (x < 0);
}
lld dot(Point a, Point b) { return RE(conj(a) * b); }
lld cross(Point a, Point b) { return IM(conj(a) * b); }
int ori(Point a, Point b, Point c) {
  return sgn(cross(b - a, c - a));
}
bool operator<(const Point &a, const Point &b) {
  return RE(a) != RE(b) ? RE(a) < RE(b) : IM(a) < IM(b);
}
int argCmp(Point a, Point b) {
  // -1 / 0 / 1 <-> < / == / > (atan2)
  int qa = (IM(a) == 0
      ? (RE(a) < 0 ? 3 : 1) : (IM(a) < 0 ? 0 : 2));
  int qb = (IM(b) == 0
      ? (RE(b) < 0 ? 3 : 1) : (IM(b) < 0 ? 0 : 2));
  if (qa != qb)
    return sgn(qa - qb);
  return sgn(cross(b, a));
}
template <typename V> llf area(const V & pt) {
  lld ret = 0;
  for (int i = 1; i + 1 < (int)pt.size(); i++)
    ret += cross(pt[i] - pt[0], pt[i+1] - pt[0]);
  return ret / 2.0;
}
Point rot90(Point p) {
  return Point{-IM(p), RE(p)};
}
Pointf projection(Pointf p, Pointf q) { // p onto q
  return dot(p, q) * q / dot(q, q);
}
