class LBD {
  int n, timer, chains;
  vector<vector<int>> G;
  vector<int> tl, tr, chain, top, dep, pa;
  // chains : number of chain
  // tl, tr[u] : subtree interval in the seq. of u
  // top[i] : top of the chain of vertex i
  // chian[u] : chain id of the chain u is on
  void predfs(int u, int f) {
    dep[u] = dep[pa[u] = f] + 1;
    for (int v : G[u]) if (v != f) {
      predfs(v, u);
      if (lowbit(chain[u]) < lowbit(chain[v]))
        chain[u] = chain[v];
    }
    if (chain[u] == 0) chain[u] = ++chains;
  }
  void dfschain(int u, int f, int t) {
    tl[u] = timer++; top[u] = t;
    for (int v : G[u])
      if (v != f and chain[v] == chain[u])
        dfschain(v, u, t);
    for (int v : G[u])
      if (v != f and chain[v] != chain[u])
        dfschain(v, u, v);
    tr[u] = timer;
  }
public:
  LBD(auto &&G_) : n((int)size(G_)),
    timer(0), chains(0), G(G_), tl(n), tr(n),
      chain(n), top(n + 1, -1), dep(n), pa(n)
    { predfs(0, 0); dfschain(0, 0, 0); }
  PII get_subtree(int u) { return {tl[u], tr[u]}; }
  vector<PII> get_path(int u, int v) {
    vector<PII> res;
    while (chain[u] != chain[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      int s = top[u];
      res.emplace_back(tl[s], tl[u] + 1);
      u = pa[s];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res.emplace_back(tl[v], tl[u] + 1);
    return res;
  }
}; // 記得在資結上對點的修改要改成對其 dfs 序的修改
