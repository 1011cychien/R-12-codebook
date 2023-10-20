struct Event {
  P d; int u, v;
  bool operator<(const Event &b) const {
    return sgn(cross(d, b.d)) > 0; }
};
P makePositive(P z) { return cmpxy(z, 0) ? -z : z; }
void rotatingSweepLine(const vector<P> &p) {
  const int n = int(p.size());
  vector<Event> e; e.reserve(n * (n - 1) / 2);
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      e.emplace_back(makePositive(p[i] - p[j]), i, j);
  sort(all(e));
  vector<int> ord(n), pos(n);
  iota(all(ord), 0);
  sort(all(ord), [&p](int i, int j) {
    return cmpxy(p[i], p[j]); });
  for (int i = 0; i < n; i++) pos[ord[i]] = i;
  const auto makeReverse = [](auto &v) {
    sort(all(v)); v.erase(unique(all(v)), v.end());
    vector<pair<int,int>> segs;
    for (size_t i = 0, j = 0; i < v.size(); i = j) {
      for (; j < v.size() && v[j] - v[i] <= j - i; j++);
      segs.emplace_back(v[i], v[j - 1] + 1 + 1);
    }
    return segs;
  };
  for (size_t i = 0, j = 0; i < e.size(); i = j) {
    /* do here */
    vector<size_t> tmp;
    for (; j < e.size() && !(e[i] < e[j]); j++)
      tmp.push_back(min(pos[e[j].u], pos[e[j].v]));
    for (auto [l, r] : makeReverse(tmp)) {
      reverse(ord.begin() + l, ord.begin() + r);
      for (int t = l; t < r; t++) pos[ord[t]] = t;
    }
  }
}

