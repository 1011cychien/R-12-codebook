vector<tuple<int, int, int>> GomoryHu(int n){
  vector<tuple<int, int, int>> rt;
  vector<int> g(n);
  for (int i = 1; i < n; ++i) {
    int t = g[i];
    flow.reset(); // clear flows on all edge
    rt.emplace_back(i, t, flow.max_flow(i, t));
    flow.walk(i); // bfs points that connected to i (use edges with .cap > 0)
    for (int j = i + 1; j < n; ++j)
      if (g[j]==t&&flow.connect(j)) // check if i can reach j
        g[j] = i;
  }
  return rt;
}
