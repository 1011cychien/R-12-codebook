class LBD {
  int timer, chains;
  vector<vector<int>> G;
  vector<int> tl, tr, chain, head, dep, pa;
  // chains : number of chain
  // tl, tr[u] : subtree interval in the seq. of u
  // head[i] : head of the chain i
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
  void dfschain(int u, int f) {
    tl[u] = timer++;
    if (head[chain[u]] == -1)
      head[chain[u]] = u;
    for (int v : G[u])
      if (v != f and chain[v] == chain[u])
        dfschain(v, u);
    for (int v : G[u])
      if (v != f and chain[v] != chain[u])
        dfschain(v, u);
    tr[u] = timer;
  }
public:
  LBD(int n) : timer(0), chains(0), G(n), tl(n), tr(n),
        chain(n), head(n + 1, -1), dep(n), pa(n) {}
  void add_edge(int u, int v) {
    G[u].push_back(v); G[v].push_back(u);
  }
  void decompose() { predfs(0, 0); dfschain(0, 0); }
  PII get_subtree(int u) { return {tl[u], tr[u]}; }
  vector<PII> get_path(int u, int v) {
    vector<PII> res;
    while (chain[u] != chain[v]) {
      if (dep[head[chain[u]]] < dep[head[chain[v]]])
        swap(u, v);
      int s = head[chain[u]];
      res.emplace_back(tl[s], tl[u] + 1);
      u = pa[s];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res.emplace_back(tl[v], tl[u] + 1);
    return res;
  }
};
