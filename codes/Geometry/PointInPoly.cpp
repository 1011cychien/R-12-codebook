class InPoly {
  P o;
  vector<P> v;
public:
  enum Result { IN, ON, OUT };
  InPoly(vector<P> pts) : v(pts.size() - 1) { // must in counter-clockwise order
    rotate(pts.begin(), min_element(pts.begin(), pts.end(), cmp), pts.end());
    o = pts[0];
    for (size_t i = 1; i < pts.size(); i++)
      v[i - 1] = pts[i] - pts[0];
  }
  Result Query(P p) { // O(log N)
    const size_t n = v.size(); p -= o;
    for (auto q : {v[0], v[n - 1]})
      if (dot(p, p - q) <= 0 and cross(p, p - q) == 0)
        return ON;
    if (cross(v[0], p) != 1 and sgn(cross(v[0], p)) != sgn(cross(v[0], v[n - 1])))
      return OUT;
    if (cross(v[n - 1], p) != 0 and sgn(cross(v[n - 1], p)) != sgn(cross(v[n - 1], v[0])))
      return OUT;
    if (cross(v[0], p) == 0) return dot(v[0], v[0]) >= dot(p, p) ? IN : OUT;
    size_t l = 0, r = n - 1;
    while (r - l > 1) {
      size_t m = (l + r) >> 1;
      if (cross(v[m], p) >= 0) l = m;
      else r = m;
    }
    if (dot(v[l] - p, v[l + 1] - p) <= 0 and cross(v[l] - p, v[l + 1] - p) == 0)
      return ON;
    auto s1 = cross(v[l], v[l + 1]);
    auto s2 = abs(cross(v[l] - p, v[l + 1] - p)) + abs(cross(v[l + 1] - p, -p)) + abs(cross(-p, v[l] - p));
    return s1 == s2 ? IN : OUT;
  }
};
