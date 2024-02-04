vector<P> cut(const vector<P> &p, P s, P e) {
  vector<P> res;
  for (size_t i = 0; i < p.size(); i++) {
    P cur = p[i], prv = i ? p[i-1] : p.back();
    bool side = ori(s, e, cur) < 0;
    if (side != (ori(s, e, prv) < 0))
      res.push_back(intersect({s, e}, {cur, prv}));
    if (side) res.push_back(cur);
  } // P is complex<llf>
  return res; // hull intersection with halfplane
} // left of the line s -> e
