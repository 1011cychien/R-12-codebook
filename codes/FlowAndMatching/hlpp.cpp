template <int maxn, typename T = int>
struct HLPP {
  const T INF = numeric_limits<T>::max();
  struct E { int to, rev; T f; };
  int n; vector<E> G[maxn]; max_heap<pair<int,int>> pq;
  T excess[maxn]; size_t arc[maxn];
  int nxt[2 * maxn], prv[2 * maxn], h[maxn], mxgap;
  HLPP(const vector<int> &deg) {
    n = (int)deg.size(); assert(n <= maxn);
    for (int i = 0; i < n; i++) G[i].reserve(deg[i]);
  }
  void add_edge(int from, int to, int f, bool isDirected = true) {
    G[from].emplace_back(to, int(G[to].size()), f);
    G[to].emplace_back(from, int(G[from].size()) - 1, isDirected ? 0 : f);
  }
  void update_h(int v, int nh) {
    if (h[v] != n)
      nxt[prv[v]] = nxt[v], prv[nxt[v]] = prv[v];
    h[v] = nh;
    if (nh == n) return;
    mxgap = max(mxgap, nh);
    if (excess[v] > 0) pq.emplace(nh, v);
    nxt[v] = nxt[nh + n]; prv[v] = nh + n;
    nxt[nh + n] = v; prv[nxt[v]] = v;
  }
  void bfs(int t) {
    for (int i = 0; i < n; i++)
      h[i] = n, nxt[i] = prv[i] = i;
    vector<int> que = {t}; h[t] = 0;
    for (size_t i = 0; i < que.size(); ++i)
      for (int v = que[i]; auto &e : G[v])
        if (h[e.to] == n && G[e.to][e.rev].f > 0)
          que.push_back(e.to), update_h(e.to, h[v] + 1);
    mxgap = h[que.back()];
  }
  void push(int v, E &e) {
    T df = min(excess[v], e.f);
    if (df == 0) return;
    if (excess[e.to] == 0) pq.emplace(h[e.to], e.to);
    e.f -= df, G[e.to][e.rev].f += df;
    excess[v] -= df, excess[e.to] += df;
  }
  bool discharge(int v) {
    int nh = n;
    for (size_t j = 0, S = G[v].size(); j < S; ++j) {
      auto i = j+arc[v]>=S ? j+arc[v]-S : j+arc[v];
      auto &e = G[v][i];
      if (e.f == 0) continue;
      if (h[v] == h[e.to] + 1) {
        push(v, e);
        if (excess[v] <= 0) return arc[v] = i, false;
      } else nh = min(nh, h[e.to] + 1);
    }
    if (nxt[h[v] + n] != h[v] + n) update_h(v, nh);
    else
      for (int oldh = h[v], &g = mxgap; g >= oldh; --g) {
        for (int i = nxt[g + n]; i < n; i = nxt[i])
          h[i] = n;
        nxt[g + n] = prv[g + n] = g + n;
      }
    return true;
  }
  T max_flow(int s, int t) {
    fill(arc, arc + n, 0); fill(excess, excess + n, 0);
    excess[s] = INF; excess[t] = -INF;
    bfs(t); for (auto &e : G[s]) push(s, e);
    int work = 0;
    while (!pq.empty()) {
      auto [hv, v] = pq.top(); pq.pop();
      if (h[v] != hv) continue;
      work += discharge(v);
      if (work > 4 * n) bfs(t), work = 0;
    }
    return excess[t] + INF;
  }
};
