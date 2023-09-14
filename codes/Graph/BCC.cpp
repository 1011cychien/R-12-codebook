class BCC {
  int n, ecnt, bcnt;
  vector<vector<pair<int, int>>> g;
  vector<int> dfn, low, bcc, stk;
  vector<bool> ap, bridge;
  void dfs(int u, int f) {
    dfn[u] = low[u] = dfn[f] + 1;
    int ch = 0;
    for (auto [v, t] : g[u]) if (bcc[t] == -1) {
      bcc[t] = 0; stk.push_back(t);
      if (dfn[v]) {
        low[u] = min(low[u], dfn[v]);
        continue;
      }
      ++ch, dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > dfn[u]) bridge[t] = true;
      if (low[v] < dfn[u]) continue;
      ap[u] = true;
      while (not stk.empty()) {
        int o = stk.back(); stk.pop_back();
        bcc[o] = bcnt;
        if (o == t) break;
      }
      bcnt += 1;
    }
    ap[u] = ap[u] and (ch != 1 or u != f);
  }
public:
  BCC(int n_) : n(n_), ecnt(0), bcnt(0), g(n), dfn(n), low(n), stk(), ap(n) {}
  void add_edge(int u, int v) {
    g[u].emplace_back(v, ecnt);
    g[v].emplace_back(u, ecnt++);
  }
  void solve() {
    bridge.assign(ecnt, false); bcc.assign(ecnt, -1);
    for (int i = 0; i < n; ++i) if (!dfn[i]) dfs(i, i);
  }
  int bcc_id(int x) const { return bcc[x]; }
  bool is_ap(int x) const { return ap[x]; }
  bool is_bridge(int x) const { return bridge[x]; }
};
