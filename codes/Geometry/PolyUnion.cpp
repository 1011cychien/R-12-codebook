llf rat(P a, P b) { return sgn(RE(b)) ? llf(RE(a))/RE(b) : llf(IM(a))/IM(b); }
llf polyUnion(vector<vector<P>>& poly) {
  llf ret = 0; // area of poly[i] must be non-negative
  rep(i,0,sz(poly)) rep(v,0,sz(poly[i])) {
    P A = poly[i][v], B = poly[i][(v + 1) % sz(poly[i])];
    vector<pair<llf, int>> segs{{0, 0}, {1, 0}};
    rep(j,0,sz(poly)) if (i != j) {
      rep(u,0,sz(poly[j])) {
        P C = poly[j][u], D = poly[j][(u + 1) % sz(poly[j])];
        if (int sc = ori(A, B, C), sd = ori(A, B, D); sc != sd) {
          llf sa = cross(D-C, A-C), sb = cross(D-C, B-C);
          if (min(sc, sd) < 0)
            segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
        } else if (!sc && !sd && j<i && sgn(dot(B-A,D-C))>0){
          segs.emplace_back(rat(C - A, B - A), 1);
          segs.emplace_back(rat(D - A, B - A), -1);
        }
      }
    }
    sort(segs.begin(), segs.end());
    for (auto &s : segs) s.first = clamp<llf>(s.first, 0, 1);
    llf sum = 0;
    int cnt = segs[0].second;
    rep(j,1,sz(segs)) {
      if (!cnt) sum += segs[j].first - segs[j - 1].first;
      cnt += segs[j].second;
    }
    ret += cross(A,B) * sum;
  }
  return ret / 2;
}
