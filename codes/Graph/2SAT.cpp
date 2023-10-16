class TwoSat { // test @ CSES Giant Pizza
private:
  int n; vector<vector<int>> G, rG, sccs;
  vector<int> ord, idx, vis, res;
  void dfs(int u) {
    vis[u] = true;
    for (int v : G[u]) if (!vis[v]) dfs(v);
    ord.push_back(u);
  }
  void rdfs(int u) {
    vis[u] = false; idx[u] = sccs.size() - 1;
    sccs.back().push_back(u);
    for (int v : rG[u]) if (vis[v]) rdfs(v);
  }
public:
  TwoSat(int n_) : n(n_), G(n), rG(n), idx(n), vis(n), res(n) {}
  void add_edge(int u, int v) {
    G[u].push_back(v); rG[v].push_back(u);
  }
  void orr(int x, int y) {
    if ((x ^ y) == 1) return;
    add_edge(x ^ 1, y); add_edge(y ^ 1, x);
  }
  bool solve() {
    for (int i = 0; i < n; ++i) if (not vis[i]) dfs(i);
    for (int u : ord | views::reverse)
      if (vis[u]) sccs.emplace_back(), rdfs(u);
    for (int i = 0; i < n; i += 2)
      if (idx[i] == idx[i + 1]) return false;
    vector<bool> c(sccs.size());
    for (size_t i = 0; i < sccs.size(); ++i)
      for (int z : sccs[i])
        res[z] = c[i], c[idx[z ^ 1]] = !c[i];
    return true;
  }
  bool get(int x) { return res[x]; }
  int get_id(int x) { return idx[x]; }
  int count() { return sccs.size(); }
};
