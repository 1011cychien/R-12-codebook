void rotatingSweepLine(P a[], int n) {
  vector<pair<int,int>> ls; ls.reserve(n*(n-1)/2);
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      ls.emplace_back(i, j);
  sort(all(ls), [&a](auto &u, auto &v){
    P zu = a[u.first] - a[u.second];
    P zv = a[v.first] - a[v.second];
    int s = sgn(RE(zu)) * sgn(RE(zv));
    if (s == 0) return RE(zu) != 0;
    return sgn(cross(zu, zv)) * s > 0;
  });
  vector<int> idx(n), p(n);
  iota(all(idx), 0);
  sort(all(idx), [&a](int i, int j) {
    return cmpxy(a[i], a[j]); });
  for (int i = 0; i < n; ++i) p[idx[i]] = i;
  for (auto [i, j]: ls) {
    // do here
    assert (abs(p[i] - p[j]) == 1);
    swap(p[i], p[j]); idx[p[i]] = i; idx[p[j]] = j;
  } // consider swap same slope together?
}
