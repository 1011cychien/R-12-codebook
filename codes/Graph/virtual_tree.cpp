vector<pair<int, int>> build(vector<int> vs) { // tree 0-base
  vector<pair<int, int>> res;
  sort(vs.begin(), vs.end(), [](int i, int j) { return dfn[i] < dfn[j]; });
  vector<int> s = {0};
  for (int v : vs) if (v != 0) {
    int o = lca(v, s.back());
    if (o != s.back()) {
      while (s.size() >= 2 and dfn[s[s.size() - 2]] >= dfn[o]) {
        res.emplace_back(s[s.size() - 2], s.back());
        s.pop_back();
      }
      if (s.back() != o) {
        res.emplace_back(s.back(), o);
        s.back() = o;
      }
    }
    s.push_back(v);
  }
  for (size_t i = 1; i < s.size(); ++i)
    res.emplace_back(s[i - 1], s[i]);
  return res;
}
