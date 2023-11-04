void build_voronoi_cells(auto &&p, auto &&res) {
  vector<vector<int>> adj(p.size());
  for (auto f: res) F3 {
    int a = f[i], b = f[R(i)];
    if (a >= p.size() || b >= p.size()) continue;
    adj[a].emplace_back(b);
  }
  // use `adj` and `p` and HPI to build cells
  for (size_t i = 0; i < p.size(); i++) {
    vector<Line> ls = frame; // the frame
    for (int j : adj[i]) {
      P m = p[i] + p[j], d = rot90(p[j] - p[i]);
      assert (norm(d) != 0);
      ls.emplace_back(m, m + d); // doubled coordinate
    } // HPI(ls)
  }
}
