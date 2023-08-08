const int inf = 1e9, V = 1021, E = 101010;
struct MMC { // O(VE)
  struct Edge { int v, u; llf c; };
  int n, m, prv[V][V], prve[V][V], vst[V];
  Edge e[E];
  vector<int> edgeID, cycle, rho;
  llf d[V][V];
  void init(int _n) { n = _n; m = 0; }
  // WARNING: TYPE matters
  void add_edge(int v, int u, llf c) { e[m++] = {v, u, c}; }
  void bellman_ford() {
    for (int i = 0; i < n; i++) d[0][i] = 0;
    for (int i = 0; i < n; i++) {
      fill(d[i + 1], d[i + 1] + n, inf);
      for (int j = 0; j < m; j++) {
        int v = e[j].v, u = e[j].u;
        if (d[i][v] < inf && d[i + 1][u] > d[i][v] + e[j].c) {
          d[i + 1][u] = d[i][v] + e[j].c;
          prv[i + 1][u] = v;
          prve[i + 1][u] = j;
        }
      }
    }
  }
  llf solve() {
    // returns inf if no cycle, mmc otherwise
    llf mmc = inf;
    int st = -1;
    bellman_ford();
    for (int i = 0; i < n; i++) {
      llf avg = -inf;
      for (int k = 0; k < n; k++) {
        if (d[n][i] < inf - eps)
          avg = max(avg, (d[n][i]-d[k][i]) / (n-k));
        else avg = max(avg, inf);
      }
      if (avg < mmc) tie(mmc, st) = tie(avg, i);
    }
    memset(vst, 0, sizeof(vst));
    edgeID.clear(); cycle.clear(); rho.clear();
    for (int i = n; !vst[st]; st = prv[i--][st]) {
      vst[st]++;
      edgeID.emplace_back(prve[i][st]);
      rho.emplace_back(st);
    }
    while (vst[st] != 2) {
      int v = rho.back(); rho.pop_back();
      cycle.emplace_back(v);
      vst[v]++;
    }
    reverse(all(edgeID));
    edgeID.resize(cycle.size());
    return mmc;
  }
} mmc;
