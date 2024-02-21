// g[i] = list of (edge.to, edge.id)
auto euler(int N, int M, int S, const auto &g) {
  vector<int> iter(N), vis(M), vv, ee;
  auto dfs = [&](auto self, int i) -> void {
    while (iter[i] < ssize(g[i])) {
      auto [j, eid] = g[i][iter[i]++];
      if (vis[eid]) continue;
      vis[eid] = true; self(self, j);
      vv.push_back(j); ee.push_back(eid);
    }
  };
  dfs(dfs, S); vv.push_back(S);
  reverse(all(vv)); reverse(all(ee));
  return pair{vv, ee};
} // 需要保證傳入的 g, S degree 符合條件；小心孤點奇點
