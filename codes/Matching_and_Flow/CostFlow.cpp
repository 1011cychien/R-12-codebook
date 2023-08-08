template <typename F, typename C> class MCMF {
  static constexpr F INF_F = numeric_limits<F>::max();
  static constexpr C INF_C = numeric_limits<C>::max();
  struct E {
    int to, r;
    F f; C c;
    E() {}
    E(int a, int b, F x, C y)
      : to(a), r(b), f(x), c(y) {}
  };
  vector<vector<E>> g;
  vector<pair<int, int>> f;
  vector<bool> inq;
  vector<F> up; vector<C> d;
  optional<pair<F, C>> step(int S, int T) {
    queue<int> q;
    for (q.push(S), d[S] = 0, up[S] = INF_F;
        not q.empty(); q.pop()) {
      int u = q.front(); inq[u] = false;
      if (up[u] == 0) continue;
      for (int i = 0; i < int(g[u].size()); ++i) {
        auto e = g[u][i]; int v = e.to;
        if (e.f <= 0 or d[v] <= d[u] + e.c)
          continue;
        d[v] = d[u] + e.c; f[v] = {u, i};
        up[v] = min(up[u], e.f);
        if (not inq[v]) q.push(v);
        inq[v] = true;
      }
    }
    if (d[T] == INF_C) return nullopt;
    for (int i = T; i != S; i = f[i].first) {
      auto &eg = g[f[i].first][f[i].second];
      eg.f -= up[T];
      g[eg.to][eg.r].f += up[T];
    }
    return pair{up[T], d[T]};
  }
public:
  MCMF(int n) : g(n),f(n),inq(n),up(n),d(n,INF_C) {}
  void add_edge(int s, int t, F c, C w) {
    g[s].emplace_back(t, int(g[t].size()), c, w);
    g[t].emplace_back(s, int(g[s].size()) - 1, 0, -w);
  }
  pair<F, C> solve(int a, int b) {
    F c = 0; C w = 0;
    while (auto r = step(a, b)) {
      c += r->first, w += r->first * r->second;
      fill(inq.begin(), inq.end(), false);
      fill(d.begin(), d.end(), INF_C);
    }
    return {c, w};
  }
};
