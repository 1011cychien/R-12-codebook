llf polyUnion(const vector<vector<P>> &p) {
  vector<tuple<P, P, int>> seg;
  for (int i = 0; i < ssize(p); i++)
    for (int j = 0, m = int(p[i].size()); j < m; j++)
      seg.emplace_back(p[i][j], p[i][(j + 1) % m], i);
  llf ret = 0; // area of p[i] must be non-negative
  for (auto [A, B, i] : seg) {
    vector<pair<llf, int>> evt{{0, 0}, {1, 0}};
    for (auto [C, D, j] : seg) {
      int sc = ori(A, B, C), sd = ori(A, B, D);
      if (sc != sd && i != j && min(sc, sd) < 0) {
        llf sa = cross(D-C, A-C), sb = cross(D-C, B-C);
        evt.emplace_back(sa / (sa - sb), sgn(sc - sd));
      } else if (!sc && !sd && j < i
          && sgn(dot(B - A, D - C)) > 0) {
        evt.emplace_back(real((C - A) / (B - A)), 1);
        evt.emplace_back(real((D - A) / (B - A)), -1);
      }
    }
    for (auto &[q, _] : evt) q = clamp<llf>(q, 0, 1);
    sort(evt.begin(), evt.end());
    llf sum = 0, last = 0; int cnt = 0;
    for (auto [q, c] : evt) {
      if (!cnt) sum += q - last;
      cnt += c; last = q;
    }
    ret += cross(A, B) * sum;
  }
  return ret / 2;
}
