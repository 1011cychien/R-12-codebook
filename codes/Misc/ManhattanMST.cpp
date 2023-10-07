vector<array<int, 3>> manhattanMST(vector<P> ps) {
  vector<int> id(ps.size()); iota(all(id), 0);
  vector<array<int, 3>> edges;
  for (int k = 0; k < 4; k++) {
    sort(all(id), [&](int i, int j) {
      return (ps[i] - ps[j]).x < (ps[j] - ps[i]).y; });
    map<int, int> sweep;
    for (int i : id) {
      for (auto it = sweep.lower_bound(-ps[i].y);
           it != sweep.end(); sweep.erase(it++)) {
        if (P d = ps[i] - ps[it->second]; d.y > d.x) break;
        else edges.push_back({d.y + d.x, i, it->second});
      }
      sweep[-ps[i].y] = i;
    }
    for (P &p : ps)
      if (k & 1) p.x = -p.x;
      else swap(p.x, p.y);
  }
  return edges; // [{w, i, j}, ...]
} // test @ yosupo judge
