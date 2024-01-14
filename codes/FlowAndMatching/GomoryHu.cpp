vector<tuple<int, int, int>> GomoryHu(int n){
  vector<tuple<int, int, int>> rt;
  vector<int> g(n);
  for (int i = 1; i < n; ++i) {
    int t = g[i];
    auto f = flow;
    rt.emplace_back(f.max_flow(i, t), i, t);
    f.walk(i); // bfs points that connected to i (use edges with .cap > 0)
    for (int j = i + 1; j < n; ++j)
      if (g[j]==t && f.connect(j)) // check if i can reach j
        g[j] = i;
  }
  return rt;
}
/* for our dinic:
 * void walk(int) { BFS(0); }
 * bool connect(int i) { return lv[i]; } */
