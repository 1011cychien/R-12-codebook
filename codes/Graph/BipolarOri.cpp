struct BipolarOrientation {
  int n; vector<vector<int>> g;
  vector<int> vis, low, pa, sgn, ord;
  BipolarOrientation(int n_) : n(n_),
    g(n), vis(n), low(n), pa(n, -1), sgn(n) {}
  void dfs(int i) {
    ord.push_back(i); low[i] = vis[i] = int(ord.size());
    for (int j : g[i])
      if (!vis[j])
        pa[j] = i, dfs(j), low[i] = min(low[i], low[j]);
      else
        low[i] = min(low[i], vis[j]);
  }
  vector<int> solve(int S, int T) {
    g[S].insert(g[S].begin(), T); dfs(S);
    vector<int> nxt(n, -1), prv(n, -1);
    nxt[S] = T; prv[T] = S; sgn[S] = -1;
    for (int i : ord) if (i != S && i != T) {
      int p = pa[i], l = ord[low[i] - 1];
      if (sgn[l] > 0) { // insert after
        nxt[i] = nxt[p]; prv[i] = p;
        if (nxt[p] != -1) prv[nxt[p]] = i;
        nxt[p] = i;
      } else {
        prv[i] = prv[p]; nxt[i] = p;
        if (prv[p] != -1) nxt[prv[p]] = i;
        prv[p] = i;
      }
      sgn[p] = -sgn[l];
    }
    vector<int> v;
    for (int x = S; x != -1; x = nxt[x]) v.push_back(x);
    return v;
  } // S, T are unique source / unique sink
  void add_edge(int a, int b) {
    g[a].emplace_back(b); g[b].emplace_back(a); }
}; // 存在 ST 雙極定向 iff 連接 (S,T) 後整張圖點雙連通
