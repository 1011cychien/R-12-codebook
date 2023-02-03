template <typename Cap, typename Wei> class MCMF {
  static constexpr auto INF_CAP = numeric_limits<Cap>::max();
  static constexpr auto INF_WEI = numeric_limits<Wei>::max();

private:
  struct E {
    int to, rev;
    Cap cap; Wei wei;
    E() {}
    E(int a, int b, Cap c, Wei d) : to(a), rev(b), cap(c), wei(d) {}
  };
  int S, T;
  vector<vector<E>> G;
  vector<pair<int, int>> f;
  vector<int> inq;
  vector<Wei> d; vector<Cap> up;
  optional<pair<Cap, Wei>> SPFA() {
    queue<int> q;
    for (q.push(S), d[S] = 0, up[S] = INF_CAP; not q.empty(); q.pop()) {
      int u = q.front(); inq[u] = false;
      if (up[u] == 0) continue;
      for (int i = 0; i < int(G[u].size()); ++i) {
        auto e = G[u][i]; int v = e.to;
        if (e.cap <= 0 or d[v] <= d[u] + e.wei)
          continue;
        d[v] = d[u] + e.wei; f[v] = {u, i};
        up[v] = min(up[u], e.cap);
        if (not inq[v]) q.push(v);
        inq[v] = true;
      }
    }
    if (d[T] == INF_WEI) return nullopt;
    for (int i = T; i != S; i = f[i].first) {
      auto &eg = G[f[i].first][f[i].second];
      eg.cap -= up[T];
      G[eg.to][eg.rev].cap += up[T];
    }
    return pair{up[T], d[T]};
  }

public:
  void init(int n) {
    G.assign(n, vector<E>());
    f.resize(n), up.resize(n);
    inq.assign(n, false), d.assign(n, INF_WEI);
  }
  void add_edge(int s, int t, Cap c, Wei w) {
    G[s].emplace_back(t, int(G[t].size()), c, w);
    G[t].emplace_back(s, int(G[s].size()) - 1, 0, -w);
  }
  pair<Cap, Wei> solve(int a, int b) {
    S = a, T = b;
    Cap c = 0; Wei w = 0;
    while (auto r = SPFA()) {
      c += r->first, w += r->first * r->second;
      fill(inq.begin(), inq.end(), false);
      fill(d.begin(), d.end(), INF_WEI);
    }
    return {c, w};
  }
};
