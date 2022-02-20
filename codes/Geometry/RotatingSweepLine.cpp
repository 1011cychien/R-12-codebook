void rotatingSweepLine(pair<int, int> a[], int n) {
  vector<pair<int, int>> l;
  l.reserve(n * (n - 1) / 2);
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      l.emplace_back(i, j);
  sort(l.begin(), l.end(), [&a](auto &u, auto &v){
    lld udx = a[u.first].first - a[u.second].first;
    lld udy = a[u.first].second - a[u.second].second;
    lld vdx = a[v.first].first - a[v.second].first;
    lld vdy = a[v.first].second - a[v.second].second;
    if (udx == 0 or vdx == 0) return not udx == 0;
    int s = sgn(udx * vdx);
    return udy * vdx * s < vdy * udx * s;
  });
  vector<int> idx(n), p(n);
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(), [&a](int i, int j){
    return a[i] < a[j]; });
  for (int i = 0; i < n; ++i) p[idx[i]] = i;
  for (auto [i, j]: l) {
    // do here
    swap(p[i], p[j]);
    idx[p[i]] = i, idx[p[j]] = j;
  }
}
