class BCC {
private:
  int n, ecnt;
  vector<vector<pair<int, int>>> g;
  vector<int> dfn, low;
  vector<bool> ap, bridge;
  void dfs(int u, int f) {
    dfn[u] = low[u] = dfn[f] + 1;
    int ch = 0;
    for (auto [v, t] : g[u]) if (v != f) {
      if (dfn[v]) {
        low[u] = min(low[u], dfn[v]);
      } else {
        ++ch, dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] > dfn[u])
          bridge[t] = true;
        if (low[v] >= dfn[u])
          ap[u] = true;
      }
    }
    ap[u] = ap[u] and (ch != 1 or u != f);
  }
public:
  void init(int n_) {
    g.assign(n = n_, vector<pair<int, int>>());
    low.assign(n, ecnt = 0);
    dfn.assign(n, 0);
    ap.assign(n, false);
  }
  void add_edge(int u, int v) {
    g[u].emplace_back(v, ecnt);
    g[v].emplace_back(u, ecnt++);
  }
  void solve() {
    bridge.assign(ecnt, false);
    for (int i = 0; i < n; ++i)
      if (not dfn[i]) dfs(i, i);
  }
  bool is_ap(int x) { return ap[x]; }
  bool is_bridge(int x) { return bridge[x]; }
};
