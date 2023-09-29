vector<vector<int>> ETCC(auto &adj) {
  const int n = static_cast<int>(adj.size());
  vector<int> up(n), low(n), in, out, nx, id;
  in = out = nx = id = vector<int>(n, -1);
  int dfc = 0, cnt = 0; Dsu dsu(n);
  auto merge = [&](int u, int v) {
    dsu.join(u, v); up[u] += up[v]; };
  auto dfs = [&](auto self, int u, int p) -> void {
    in[u] = low[u] = dfc++;
    for (int v : adj[u]) if (v != u) {
      if (v == p) { p = -1; continue; }
      if (in[v] == -1) {
        self(self, v, u);
        if (nx[v] == -1 && up[v] <= 1) {
          up[u] += up[v]; low[u] = min(low[u], low[v]);
          continue;
        }
        if (up[v] == 0) v = nx[v];
        if (low[u] > low[v])
          low[u] = low[v], swap(nx[u], v);
        for (; v != -1; v = nx[v]) merge(u, v);
      } else if (in[v] < in[u]) {
        low[u] = min(low[u], in[v]); up[u]++;
      } else {
        for (int &x = nx[u]; x != -1 &&
            in[x] <= in[v] && in[v] < out[x]; x = nx[x])
          merge(u, x);
        up[u]--;
      }
    }
    out[u] = dfc;
  };
  for (int i = 0; i < n; i++)
    if (in[i] == -1) dfs(dfs, i, -1);
  for (int i = 0; i < n; i++)
    if (dsu.anc(i) == i) id[i] = cnt++;
  vector<vector<int>> comps(cnt);
  for (int i = 0; i < n; i++)
    comps[id[dsu.anc(i)]].push_back(i);
  return comps;
} // test @ yosupo judge
