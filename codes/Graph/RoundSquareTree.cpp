struct RST {
  int n; vector<vector<int>> T;
  RST(auto &G) : n(G.size()), T(n) {
    vector<int> stk, vis(n), low(n);
    auto dfs = [&](auto self, int u, int d) -> void {
      low[u] = vis[u] = d; stk.push_back(u);
      for (int v : G[u]) if (!vis[v]) {
        self(self, v, d + 1);
        if (low[v] == vis[u]) {
          int cnt = T.size(); T.emplace_back();
          for (int x = -1; x != v; stk.pop_back())
            T[cnt].push_back(x = stk.back());
          T[u].push_back(cnt); // T is rooted
        } else low[u] = min(low[u], low[v]);
      } else low[u] = min(low[u], vis[v]);
    };
    for (int u = 0; u < N; u++)
      if (!vis[u]) dfs(dfs, u, 1);
  } // T may be forest; after dfs, stk are the roots
}; // test @ 2020 Shanghai K
