class Centroid {
  vector<vector<pair<int, int>>> g; // g[u] = {(v, w)}
  vector<int> pa, dep, vis, sz, mx;
  vector<vector<int64_t>> Dist;
  vector<int64_t> Sub, Sub2;
  vector<int> Cnt, Cnt2;
  void DfsSz(vector<int> &tmp, int x) {
    vis[x] = true, sz[x] = 1, mx[x] = 0;
    for (auto [u, w] : g[x]) if (not vis[u]) {
      DfsSz(tmp, u); sz[x] += sz[u];
      mx[x] = max(mx[x], sz[u]);
    }
    tmp.push_back(x);
  }
  void DfsDist(int x, int64_t D = 0) {
    Dist[x].push_back(D); vis[x] = true;
    for (auto [u, w] : g[x])
      if (not vis[u]) DfsDist(u, D + w);
  }
  void DfsCen(int x, int D, int p) {
    vector<int> tmp; DfsSz(tmp, x);
    int M = int(tmp.size()), C = -1;
    for (int u : tmp)
      if (max(M - sz[u], mx[u]) * 2 <= M) C = u;
    for (int u : tmp) vis[u] = false;
    DfsDist(C);
    for (int u : tmp) vis[u] = false;
    pa[C] = p, vis[C] = true, dep[C] = D;
    for (auto [u, w] : g[C])
      if (not vis[u]) DfsCen(u, D + 1, C);
  }
public:
  Centroid(int N) : g(N), pa(N), dep(N),
    vis(N), sz(N), mx(N), Dist(N), 
    Sub(N), Sub2(N), Cnt(N), Cnt2(N) {}
  void AddEdge(int u, int v, int w) {
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  void Build() { DfsCen(0, 0, -1); }
  void Mark(int v) {
    int x = v, z = -1;
    for (int i = dep[v]; i >= 0; --i) {
      Sub[x] += Dist[v][i], Cnt[x]++;
      if (z != -1)
        Sub2[z] += Dist[v][i], Cnt2[z]++;
      x = pa[z = x];
    }
  }
  int64_t Query(int v) {
    int64_t res = 0;
    int x = v, z = -1;
    for (int i = dep[v]; i >= 0; --i) {
      res += Sub[x] + 1LL * Cnt[x] * Dist[v][i];
      if (z != -1)
        res -= Sub2[z] + 1LL * Cnt2[z] * Dist[v][i];
      x = pa[z = x];
    }
    return res;
  }
}; // pa, dep are centroid tree attributes
