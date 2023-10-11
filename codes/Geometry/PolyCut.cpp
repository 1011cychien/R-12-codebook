using P = PTF;
vector<P> cut(const vector<P>& poly, P s, P e) {
  vector<P> res;
  for (size_t i = 0; i < poly.size(); i++) {
    P cur = poly[i], prv = i ? poly[i-1] : poly.back();
    bool side = ori(s, e, cur) < 0;
    if (side != (ori(s, e, prv) < 0))
      res.push_back(intersect({s, e}, {cur, prv}));
    if (side)
      res.push_back(cur);
  }
  return res;
}
