void build_voronoi_cells(auto &&p, auto &&res) {
  vector<vector<int>> adj(p.size());
  map<pair<lld,lld>,int> mp;
  for (size_t i = 0; i < p.size(); ++i)
    mp[{RE(p[i]), IM(p[i])}] = i;
  const auto Get = [&](P z) {
    auto it = mp.find({RE(z), IM(z)});
    return it==mp.end() ? -1 : it->second;
  };
  for (Tri *t: res) F3 {
    P A = t->p[i], B = t->p[R(i)];
    int a = Get(A), b = Get(B);
    if (a == -1 || b == -1) continue;
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
