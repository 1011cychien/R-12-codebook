template <typename F, typename C> class MCMF {
  static constexpr F INF_F = numeric_limits<F>::max();
  static constexpr C INF_C = numeric_limits<C>::max();
  vector<tuple<int, int, F, C>> es;
  vector<vector<int>> g; vector<int> pre, inq;
  vector<F> f; vector<C> d, pot;
  void spfa(auto &&init) {
    ranges::fill(inq, false);
    ranges::fill(d, INF_C);
    ranges::fill(pre, -1);
    queue<int> q; init(q);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      inq[u] = false;
      for (int j : g[u]) if (f[j] > 0) {
        auto [from, to, cap, w] = es[j];
        if (d[to] > d[u] + w) {
          d[to] = d[u] + w; pre[to] = j;
          if (!inq[to])
            inq[to] = true, q.push(to);
        }
      }
    }
  }
public:
  MCMF(int n) : g(n), pre(n), inq(n) {}
  void add_edge(int s, int t, F c, C w) {
    g[s].push_back((int)es.size());
    es.emplace_back(s, t, c, w);
    g[t].push_back((int)es.size());
    es.emplace_back(t, s, 0, -w);
  }
  pair<F, C> solve(int s, int t, C mx = INF_C / INF_F) {
    add_edge(t, s, INF_F, -mx);
    f.resize(es.size());
    d.resize(g.size()); pot.resize(g.size());
    for (F I = INF_F ^ (INF_F / 2); I; I >>= 1) {
      for (auto &fi : f) fi *= 2;
      for (size_t i = 0; i < f.size(); i += 2) {
        auto [u, v, c, w] = es[i];
        if (~c & I) continue;
        if (f[i]) { f[i] += 1; continue; }
        spfa([&](auto &q) { d[v] = 0; q.push(v); });
        if (d[u] == INF_C || d[u] + w >= 0) {
          f[i] += 1;
        } else {
          f[i + 1] += 1;
          while (u != v) {
            int x = pre[u];
            f[x] -= 1; f[x ^ 1] += 1;
            u = get<0>(es[x]);
          }
        }
      }
    }
    C w = 0;
    for (size_t i = 1; i + 2 < f.size(); i += 2)
      w -= f[i] * get<3>(es[i]);
    return {f.back(), w};
  }
  vector<C> get_potential() {
    spfa([&](auto &q) {
      for (int i = 0; i < ssize(g); i++)
        d[i] = 0, q.push(i);
    });
    return d;
  }
  vector<F> get_cap() const {
    vector<F> res;
    for (size_t i = 1; i < f.size(); i += 2)
      res.push_back(f[i]);
    return res;
  }
};
