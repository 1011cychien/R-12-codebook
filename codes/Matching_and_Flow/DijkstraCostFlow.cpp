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
  vector<F> up;
  vector<C> d, h;
  optional<pair<F, C>> step(int S, int T) {
    priority_queue<pair<C, int>> q;
    q.emplace(d[S] = 0, S), up[S] = INF_F;
    while (not q.empty()) {
      auto [l, u] = q.top(); q.pop();
      if (up[u] == 0 or l != -d[u]) continue;
      for (int i = 0; i < int(g[u].size()); ++i) {
        auto e = g[u][i]; int v = e.to;
        auto nd = d[u] + e.c + h[u] - h[v];
        if (e.f <= 0 or d[v] <= nd)
          continue;
        f[v] = {u, i};
        up[v] = min(up[u], e.f);
        q.emplace(-(d[v] = nd), v);
      }
    }
    if (d[T] == INF_C) return nullopt;
    for (size_t i = 0; i < d.size(); i++) h[i]+=d[i];
    for (int i = T; i != S; i = f[i].first) {
      auto &eg = g[f[i].first][f[i].second];
      eg.f -= up[T];
      g[eg.to][eg.r].f += up[T];
    }
    return pair{up[T], h[T]};
  }

public:
  MCMF(int n) : g(n),f(n),up(n),d(n, INF_C),h(n) {}
  void add_edge(int s, int t, F c, C w) {
    g[s].emplace_back(t, int(g[t].size()), c, w);
    g[t].emplace_back(s, int(g[s].size()) - 1, 0, -w);
  }
  pair<F, C> solve(int a, int b) {
    F c = 0; C w = 0;
    while (auto r = step(a, b)) {
      c += r->first, w += r->first * r->second;
      fill(d.begin(), d.end(), INF_C);
    }
    return {c, w};
  }
};
