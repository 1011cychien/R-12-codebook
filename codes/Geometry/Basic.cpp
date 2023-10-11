#define IM imag
#define RE real
using lld = int64_t;
using llf = long double;
using PT = std::complex<lld>;
using PTF = std::complex<llf>;
using P = PT;
llf abs(P p) { return sqrtl(norm(p)); }
PTF toPTF(PT p) { return PTF{RE(p), IM(p)}; }
int sgn(lld x) { return (x > 0) - (x < 0); }
lld dot(P a, P b) { return RE(conj(a) * b); }
lld cross(P a, P b) { return IM(conj(a) * b); }
int ori(P a, P b, P c) {
  return sgn(cross(b - a, c - a));
}
int quad(P p) {
  return (IM(p) == 0) // use sgn for PTF
    ? (RE(p) < 0 ? 3 : 1) : (IM(p) < 0 ? 0 : 2);
}
int argCmp(P a, P b) {
  // returns 0/+-1, starts from theta = -PI
  int qa = quad(a), qb = quad(b);
  if (qa != qb) return sgn(qa - qb);
  return sgn(cross(b, a));
}
P rot90(P p) { return P{-IM(p), RE(p)}; }
template <typename V> llf area(const V & pt) {
  lld ret = 0;
  for (int i = 1; i + 1 < (int)pt.size(); i++)
    ret += cross(pt[i] - pt[0], pt[i+1] - pt[0]);
  return ret / 2.0;
}
template <typename V> PTF center(const V & pt) {
  P ret = 0; lld A = 0;
  for (int i = 1; i + 1 < (int)pt.size(); i++) {
    lld cur = cross(pt[i] - pt[0], pt[i+1] - pt[0]);
    ret += (pt[i] + pt[i + 1] + pt[0]) * cur; A += cur;
  }
  return toPTF(ret) / llf(A * 3);
}
PTF project(PTF p, PTF q) { // p onto q
  return dot(p, q) * q / dot(q, q); // dot<llf>
}
