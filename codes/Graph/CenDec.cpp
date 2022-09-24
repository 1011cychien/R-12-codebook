struct Centroid {
  vector<vector<int64_t>> Dist;
  vector<int> Pa, Dep;
  vector<int64_t> Sub, Sub2;
  vector<int> Cnt, Cnt2;
  vector<int> vis, sz, mx, tmp
  void DfsSz(int x) {
    vis[x] = true; sz[x] = 1; mx[x] = 0;
    for (auto [u, w] : g[x]) {
      if (vis[u]) continue;
      DfsSz(u);
      sz[x] += sz[u];
      mx[x] = max(mx[x], sz[u]);
    }
    tmp.push_back(x);
  }
  void DfsDist(int x, int64_t D = 0) {
    Dist[x].push_back(D); vis[x] = true;
    for (auto [u, w] : g[x])
      if (not vis[u]) DfsDist(u, D + w);
  }
  void DfsCen(int x, int D = 0, int p = -1) {
    tmp.clear(); DfsSz(x);
    int M = tmp.size();
    int C = -1;
    for (int u : tmp) {
      if (max(M - sz[u], mx[u]) * 2 <= M) C = u;
      vis[u] = false;
    }
    DfsDist(C);
    for (int u : tmp) vis[u] = false;
    Pa[C] = p; vis[C] = true; Dep[C] = D;
    for (auto [u, w] : g[C])
      if (not vis[u]) DfsCen(u, D + 1, C);
  }
  Centroid(int N, vector<vector<pair<int,int>>> g)
    : Sub(N), Sub2(N), Cnt(N), Cnt2(N), Dist(N),
    Pa(N), Dep(N), vis(N), sz(N), mx(N)
    { DfsCen(0); }
  void Mark(int v) {
    int x = v, z = -1;
    for (int i = Dep[v]; i >= 0; --i) {
      Sub[x] += Dist[v][i]; Cnt[x]++;
      if (z != -1) {
        Sub2[z] += Dist[v][i];
        Cnt2[z]++;
      }
      z = x; x = Pa[x];
    }
  }
  int64_t Query(int v) {
    int64_t res = 0;
    int x = v, z = -1;
    for (int i = Dep[v]; i >= 0; --i) {
      res += Sub[x] + 1LL * Cnt[x] * Dist[v][i];
      if (z != -1) res-=Sub2[z]+1LL*Cnt2[z]*Dist[v][i];
      z = x; x = Pa[x];
    }
    return res;
  }
};
