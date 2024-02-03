class SCC { // test @ library checker
protected:
  int n, dfc, nscc; vector<vector<int>> G;
  vector<int> vis, low, idx, stk;
  void dfs(int i) {
    vis[i] = low[i] = ++dfc;
    stk.push_back(i);
    for (int j : G[i]) {
      if (!vis[j]) {
        dfs(j);
        low[i] = min(low[i], low[j]);
      } else if (vis[j] != -1) {
        low[i] = min(low[i], vis[j]);
      }
    }
    if (low[i] == vis[i]) {
      while (true) {
        int x = stk.back(); stk.pop_back();
        idx[x] = nscc; vis[x] = -1;
        if (x == i) break;
      }
      ++nscc;
    }
  }
public:
  SCC(int n_) : n(n_), dfc(0), nscc(0), G(n),
    vis(n), low(n), idx(n) {}
  void add_edge(int u, int v) { G[u].push_back(v); }
  void solve() {
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(i); }
  int get_id(int x) { return idx[x]; }
  int count() { return nscc; }
};
