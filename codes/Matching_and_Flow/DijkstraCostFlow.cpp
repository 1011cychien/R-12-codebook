// kN = #(vertices)
// MCMF.{Init, AddEdge, MincostMaxflow}
// MincostMaxflow(source, sink, flow_limit, &cost)
//   => flow
using Pii = pair<int, int>;
constexpr int kInf = 0x3f3f3f3f, kN = 500;
struct Edge {
  int to, rev, cost, flow;
};
struct MCMF { // 0-based
  int n{}, m{}, s{}, t{};
  vector<Edge> graph[kN];
  // Larger range for relabeling
  int64_t dis[kN] = {}, h[kN] = {};
  int p[kN] = {};
  void Init(int nn) {
    n = nn;
    for (int i = 0; i < n; i++) graph[i].clear();
  }
  void AddEdge(int u, int v, int f, int c) {
    graph[u].push_back({v,
      static_cast<int>(graph[v].size()), c, f});
    graph[v].push_back(
      {u, static_cast<int>(graph[u].size()) - 1,
        -c, 0});
  }
  bool Dijkstra(int &max_flow, int64_t &cost) {
    priority_queue<Pii, vector<Pii>, greater<>> pq;
    fill_n(dis, n, kInf);
    dis[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
      auto u = pq.top();
      pq.pop();
      int v = u.second;
      if (dis[v] < u.first) continue;
      for (auto &e : graph[v]) {
        auto new_dis =
          dis[v] + e.cost + h[v] - h[e.to];
        if (e.flow > 0 && dis[e.to] > new_dis) {
          dis[e.to] = new_dis;
          p[e.to] = e.rev;
          pq.emplace(dis[e.to], e.to);
        }
      }
    }
    if (dis[t] == kInf) return false;
    for (int i = 0; i < n; i++) h[i] += dis[i];
    int d = max_flow;
    for (int u = t; u != s;
         u = graph[u][p[u]].to) {
      auto &e = graph[u][p[u]];
      d = min(d, graph[e.to][e.rev].flow);
    }
    max_flow -= d;
    cost += int64_t(d) * h[t];
    for (int u = t; u != s;
         u = graph[u][p[u]].to) {
      auto &e = graph[u][p[u]];
      e.flow += d;
      graph[e.to][e.rev].flow -= d;
    }
    return true;
  }
  int MincostMaxflow(
    int ss, int tt, int max_flow, int64_t &cost) {
    this->s = ss, this->t = tt;
    cost = 0;
    fill_n(h, n, 0);
    auto orig_max_flow = max_flow;
    while (Dijkstra(max_flow, cost) && max_flow) {}
    return orig_max_flow - max_flow;
  }
};

