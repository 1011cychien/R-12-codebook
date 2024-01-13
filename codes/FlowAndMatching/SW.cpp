void add_edge(auto &w, int u, int v, int c) {
  w[u][v] += c; w[v][u] += c; }
auto phase(const auto &w, int n, vector<int> id) {
  vector<lld> g(n); int s = -1, t = -1;
  while (!id.empty()) {
    int c = -1;
    for (int i : id) if (c == -1 || g[i] > g[c]) c = i;
    s = t; t = c;
    id.erase(ranges::find(id, c));
    for (int i : id) g[i] += w[c][i];
  }
  return tuple{s, t, g[t]};
}
lld mincut(auto w, int n) {
  lld cut = numeric_limits<lld>::max();
  vector<int> id(n); iota(all(id), 0);
  for (int i = 0; i < n - 1; ++i) {
    auto [s, t, gt] = phase(w, n, id);
    id.erase(ranges::find(id, t));
    cut = min(cut, gt);
    for (int j = 0; j < n; ++j)
      w[s][j] += w[t][j], w[j][s] += w[j][t];
  }
  return cut;
} // O(V^3), can be O(VE + V^2 log V)?
