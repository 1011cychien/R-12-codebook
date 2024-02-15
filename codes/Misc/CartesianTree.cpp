auto CartesianTree(const auto &a) {
  const int n = (int)a.size(); vector<int> pa(n+1, -1);
  for (int i = 1; i < n; i++) {
    int &p = pa[i] = i - 1, l = n;
    while (p != -1 && a[i] < a[p])
      tie(l, pa[l], p, pa[p]) = tuple(p, p, pa[p], i);
  }
  return pa.pop_back(), pa;
} // root is minimum
