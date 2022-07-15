#define IM imag
#define RE real
using lld = int64_t;
using llf = long double;
using PT = std::complex<lld>;
using PTF = std::complex<llf>;
auto toPTF(PT p) { return PTF{RE(p), IM(p)}; }
int sgn(lld x) { return (x > 0) - (x < 0); }
lld dot(PT a, PT b) { return RE(conj(a) * b); }
lld cross(PT a, PT b) { return IM(conj(a) * b); }
int ori(PT a, PT b, PT c) {
  return sgn(cross(b - a, c - a));
}
bool operator<(const PT &a, const PT &b) {
  return RE(a) != RE(b) ? RE(a) < RE(b) : IM(a) < IM(b);
}
int quad(PT p) {
  return (IM(p) == 0) // use sgn for PTF
    ? (RE(p) < 0 ? 3 : 1) : (IM(p) < 0 ? 0 : 2);
}
int argCmp(PT a, PT b) {
  // -1 / 0 / 1 <-> < / == / > (atan2)
  int qa = quad(a), qb = quad(b);
  if (qa != qb) return sgn(qa - qb);
  return sgn(cross(b, a));
}
template <typename V> llf area(const V & pt) {
  lld ret = 0;
  for (int i = 1; i + 1 < (int)pt.size(); i++)
    ret += cross(pt[i] - pt[0], pt[i+1] - pt[0]);
  return ret / 2.0;
}
PT rot90(PT p) { return PT{-IM(p), RE(p)}; }
PTF project(PTF p, PTF q) { // p onto q
  return dot(p, q) * q / dot(q, q);
}
llf FMOD(llf x) {
  if (x < -PI) x += PI * 2;
  if (x > PI) x -= PI * 2;
  return x;
}
